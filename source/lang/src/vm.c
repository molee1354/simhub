#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// check for platform
#ifdef _WIN64
#include <dos.h>
#else
#include <unistd.h>
#endif

#include "chunk.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "object.h"
#include "memory.h"
#include "value.h"
#include "vm.h"

/**
 * @brief Global vm instance to be referred to by all the methods. 
 * May later be an argument to each of the functions.
 *
 */
VM vm;

// Runtime error function declaration
static void runtimeError(const char* format, ...);

/**
 * @brief Defining native "clock()" function.
 *
 * @param argcount The number of arguments 
 * @param args The arguments
 * @return Value The elapsed time since the program started running
 */
static Value clockNative(int argCount, Value* args) {
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}

static Value sleepNative(int argCount, Value* args) {
    if (argCount > 1) {
        runtimeError("Too many arguments provided : %d", argCount);
        return NULL_VAL;
    }
    if (!IS_NUMBER(args[0])) {
        runtimeError("Incorrect argument type.");
        return NULL_VAL;
    }
    int waitFor = (int)AS_NUMBER(args[0]);

    /* clock_t timeStart = clock();
    while (clock() < timeStart + waitFor)
        ; */
    sleep(waitFor);
    return NULL_VAL;
}

/**
 * @brief Defining native "puts()" function.
 *
 * @param argcount The number of arguments 
 * @param args The arguments
 * @return Value NULL_VAL
 */
static Value putsNative(int argCount, Value* args ) {
    if (argCount > 1) {
        runtimeError("Too many arguments provided : %d", argCount);
        return NULL_VAL;
    }
    if (!IS_STRING(args[0])) {
        runtimeError("Incorrect argument type.");
        return NULL_VAL;
    }
    printf("%s\n", AS_CSTRING(args[0]));
    return NULL_VAL;
}

static void resetStack() {
    // setting the stackTop pointer to the beginning of the stack
    vm.stackTop = vm.stack;
    vm.frameCount = 0;
    vm.openUpvalues = NULL;
}

/**
 * @brief Method to handle runtime errors
 * @param format The print format for error messaging
 *
 */
static void runtimeError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    /* Running through the stacktrace to track runtime errors
     * set vm.frameCount-1 since we want the stack trace to point to the 
     * previous failed instruction
     */
    for (int i = vm.frameCount-1; i>=0; i--) {
        CallFrame* frame = &vm.frames[i];
        ObjFunction* function = frame->closure->function;
        size_t instruction = frame->ip - function->chunk.code - 1;
        fprintf(stderr, "[line %d] in ",
                function->chunk.lines[instruction]);
        if (function->name == NULL) {
            fprintf(stderr, "script\n");
        } else{
            fprintf(stderr, "%s()\n", function->name->chars);
        }
    }
    resetStack();
}

/**
 * @brief Method to define new native functions. It takes a pointer to a C
 * function and the name it will be known in the language implementation
 *
 * @param name Name of native function
 * @param function Pointer to C function
 */
static void defineNative(const char* name, NativeFn function) {
    push( OBJ_VAL(copyString(name, (int)strlen(name))) );
    push( OBJ_VAL(newNative(function)) );
    tableSet(&vm.globals, AS_STRING(vm.stack[0]), vm.stack[1]);
    pop();
    pop();
}

void initVM() {
    resetStack();
    vm.objects = NULL;

    vm.bytesAllocated = 0;
    vm.nextGC = 1024 * 1024; // arbitrary initial starting threshold

    vm.grayCount = 0;
    vm.grayCapacity = 0;
    vm.grayStack = NULL;

    initTable(&vm.globals);
    initTable(&vm.strings);

    // defining native functions
    defineNative("clock", clockNative);
    defineNative("puts", putsNative);
    defineNative("sleep", sleepNative);
}

void freeVM() {
    freeTable(&vm.globals);
    freeTable(&vm.strings);
    freeObjects();
}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static Value peek(int distance) {
    return vm.stackTop[-1 - distance];
}

/**
 * @brief Method to call a function object
 *
 * @param function Pointer to the function to call
 * @param argCount The number of arguments to the function
 * @return bool True
 */
static bool call(ObjClosure* closure, int argCount) {
    // checking argument numbers
    if (argCount != closure->function->arity) {
        runtimeError("Expected %d arguments but got %d.",
                closure->function->arity, argCount);
        return false;
    }
    if (vm.frameCount == FRAMES_MAX) {
        runtimeError("Stack overflow.");
        return false;
    }
    CallFrame* frame = &vm.frames[vm.frameCount++];
    frame->closure = closure;
    frame->ip = closure->function->chunk.code;

    // ensuring that the arguments on teh stack line up with func params
    frame->slots = vm.stackTop - argCount - 1;
    return true;
}

/**
 * @brief Method to execute the call to a callable object
 *
 * @param callee Object to call
 * @param argCount The number of arguments
 * @return bool True if object is callable.
 */
static bool callValue(Value callee, int argCount) {
    if (IS_OBJ(callee)) {
        switch (OBJ_TYPE(callee)) {
            case OBJ_CLOSURE:
                return call(AS_CLOSURE(callee), argCount);
            case OBJ_NATIVE:
                NativeFn native = AS_NATIVE(callee);
                Value result = native(argCount, vm.stackTop-argCount);
                vm.stackTop -= argCount + 1;
                push(result);
                return true;
            default:
                break; // non-callable object type
        }
    }
    runtimeError("Can only call functions and classes.");
    return false;
}

/**
 * @brief Method to capture a new upvalue
 *
 * @param local The value to capture
 * @return ObjUpvalue* A pointer to the caputred upvalue
 */
static ObjUpvalue* captureUpvalue(Value* local) {
    ObjUpvalue* prevUpvalue = NULL;
    ObjUpvalue* upvalue = vm.openUpvalues;
    // traversing the linked list of upvalues
    while (upvalue != NULL && upvalue->location > local) {
        prevUpvalue = upvalue;
        upvalue = upvalue->next;
    }

    if (upvalue != NULL && upvalue->location == local) {
        return upvalue; // return an existing upvalue
    }

    ObjUpvalue* createdUpvalue = newUpvalue(local);
    createdUpvalue->next = upvalue;

    if (prevUpvalue == NULL) {
        vm.openUpvalues = createdUpvalue; // add to head if empty head 
    } else {
        prevUpvalue->next = createdUpvalue; // add to after prev if not empty
    }
    return createdUpvalue;
}

static void closeUpvalues(Value* last) {
    while (vm.openUpvalues != NULL &&
           vm.openUpvalues->location >= last) {
        ObjUpvalue* upvalue = vm.openUpvalues;
        upvalue->closed = *upvalue->location;
        upvalue->location = &upvalue->closed;
        vm.openUpvalues = upvalue->next;
    }
}

/**
 * @brief Method to determine if a value is "falsey"
 *
 * @param value Value to check false-ness
 * @return True if value is falsey
 */
static bool isFalsey(Value value) {
    return IS_NULL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

/**
 * @brief Method to convert a number to a string.
 *
 * @param num Number to convert
 * @param length Number of characters in the number
 * @return char* Pointer to the head of the character array representation.
 */
static char* toChar(double num, int length) {
    char* str = (char*)malloc(length+1);
    if (str == NULL) {
        return NULL;
    }
    snprintf(str, length+1, "%g", num);
    return str;
}

/**
 * @brief Method to convert a number to a string. Pops the topmost value in
 * the stack, converts it to a string, and pushes it back.
 *
 * @param value Number value to convert to string
 */
static void toString(Value value) {
    if (!IS_NUMBER(value)) {
        runtimeError("Unsupported type conversion to string.");
    }
    double num = (double)AS_NUMBER(value);
    int length;
    length = snprintf(NULL, 0, "%g", num);
    char* numStr = toChar(num, length);
    char* chars = ALLOCATE(char, length+1);
    memcpy(chars, numStr, length);

    ObjString* conversion = takeString(chars, length);
    pop();
    push(OBJ_VAL(conversion));
    free(numStr);
}

static void concatenate() {
    
    if (!IS_STRING(peek(0)) && IS_STRING(peek(1))) {
        toString(peek(0));
    } else if (IS_STRING(peek(0)) && !IS_STRING(peek(1))) {
        Value temp = peek(0);
        pop();
        toString(peek(0));
        push(temp);
    }

    ObjString* b = AS_STRING(peek(0));
    ObjString* a = AS_STRING(peek(1));

    // the total length of the new string
    int length = a->length + b->length;
    char* chars = ALLOCATE(char, length+1);
    memcpy(chars, a->chars, a->length);
    memcpy(chars + a->length, b->chars, b->length); // ptr offset by a->length
    chars[length] = '\0';

    ObjString* result = takeString(chars, length);
    pop();
    pop();
    push(OBJ_VAL(result));
}

static InterpretResult run() {
    CallFrame* frame = &vm.frames[vm.frameCount-1];

// ip set to the instruction about to be executed
#define READ_BYTE()     ( *frame->ip++ ) 

#define READ_SHORT() \
    ( frame->ip += 2, \
      (uint16_t)((frame->ip[-2] << 8) | frame->ip[-1]) )

#define READ_CONSTANT() \
    ( frame->closure->function->chunk.constants.values[READ_BYTE()] )

#define READ_STRING()   AS_STRING(READ_CONSTANT())

// macro for binary operation handling
#define BINARY_OP(valueType, op) \
    do { \
      if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
        runtimeError("Operands must be numbers."); \
        return INTERPRET_RUNTIME_ERROR; \
      } \
      double b = AS_NUMBER(pop()); \
      double a = AS_NUMBER(pop()); \
      push(valueType(a op b)); \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        // printing the stack 
        printf("          ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        // pass in the current callframe instead of the vm's chunk and ip fields
        disassembleInstruction( &frame->closure->function->chunk,
                (int)(frame->ip - frame->closure->function->chunk.code) );
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }

            case OP_NULL:  push(NULL_VAL); break;
            case OP_TRUE:  push(BOOL_VAL(true)); break;
            case OP_FALSE: push(BOOL_VAL(false)); break;
            case OP_POP:   pop(); break;
            case OP_SET_LOCAL: {
                uint8_t slot = READ_BYTE();
                frame->slots[slot] = peek(0);
                break;
            }
            case OP_GET_LOCAL: {
                uint8_t slot = READ_BYTE();
                push(frame->slots[slot]);
                break;
            }
            case OP_GET_GLOBAL: {
                ObjString* name = READ_STRING();
                Value value;
                if (!tableGet(&vm.globals, name, &value)) {
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(value);
                break;
            }
            case OP_DEFINE_GLOBAL: {
                ObjString* name = READ_STRING();    
                tableSet(&vm.globals, name, peek(0));
                pop();
                break;
            }

            case OP_SET_GLOBAL: {
                ObjString* name = READ_STRING();
                if (tableSet(&vm.globals, name, peek(0))) {
                    tableDelete(&vm.globals, name);
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_GET_UPVALUE: {
                uint8_t slot = READ_BYTE();
                push(*frame->closure->upvalues[slot]->location);
                break;
            }
            case OP_SET_UPVALUE: {
                uint8_t slot = READ_BYTE();
                *frame->closure->upvalues[slot]->location = peek(0);
                break;
            }
            case OP_EQUAL: {
                Value b = pop();
                Value a = pop();
                push(BOOL_VAL( valuesEqual(a, b)) );
                break;
            }

            case OP_GREATER:  BINARY_OP(BOOL_VAL, >); break;
            case OP_LESS:     BINARY_OP(BOOL_VAL, <); break;

            case OP_ADD: {
                if ( IS_STRING(peek(0)) || IS_STRING(peek(1)) ) {
                    concatenate();
                } else if( IS_NUMBER(peek(0)) && IS_NUMBER(peek(1)) ) {
                    double b = AS_NUMBER(pop());
                    double a = AS_NUMBER(pop());
                    push(NUMBER_VAL(a+b));
                } else {
                    runtimeError(
                            "Operands must be two numbers or two strings.");
                    return INTERPRET_RUNTIME_ERROR;;
                }
                break;
            }
            case OP_SUBTRACT: BINARY_OP(NUMBER_VAL, -); break;
            case OP_MULTIPLY: BINARY_OP(NUMBER_VAL, *); break;
            case OP_DIVIDE:   BINARY_OP(NUMBER_VAL, /); break;
            case OP_MOD: {
                if ( (IS_NUMBER(peek(0)) && IS_NUMBER(peek(0))) &&
                     (AS_NUMBER(peek(0)) == (int)AS_NUMBER(peek(0))) &&
                     (AS_NUMBER(peek(1)) == (int)AS_NUMBER(peek(1))) 
                   ) {
                    
                    int b = (int)AS_NUMBER(pop());
                    int a = (int)AS_NUMBER(pop());
                    push(NUMBER_VAL(a%b));
                } else {
                    runtimeError(
                            "Operands must be two integers.");
                    return INTERPRET_RUNTIME_ERROR;;
                }
                break;
            }

            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;

            case OP_NEGATE: {
                if (!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be a number.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                push( NUMBER_VAL( -AS_NUMBER(pop()) ) );
                break;
            }
            case OP_PRINT: {
                printValue(pop());
                printf("\n");
                break;
            }
            case OP_JUMP: {
                uint16_t offset = READ_SHORT();
                frame->ip += offset;
                break;
            }
            case OP_JUMP_IF_FALSE: {
                uint16_t offset = READ_SHORT();
                if (isFalsey(peek(0))) frame->ip += offset;
                break;
            }
            case OP_LOOP: {
                uint16_t offset = READ_SHORT();
                frame->ip -= offset;
                break;
            }
            case OP_CALL: {
                int argCount = READ_BYTE();
                if (!callValue(peek(argCount), argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                frame = &vm.frames[vm.frameCount-1];
                break;
            }
            case OP_CLOSURE: {
                ObjFunction* function = AS_FUNCTION(READ_CONSTANT());
                ObjClosure* closure = newClosure(function);
                push(OBJ_VAL(closure));
                for (int i=0; i < closure->upvalueCount; i++) {
                    uint8_t isLocal = READ_BYTE();
                    uint8_t index = READ_BYTE();
                    if (isLocal) {
                        closure->upvalues[i] = 
                            captureUpvalue(frame->slots + index);
                    } else {
                        closure->upvalues[i] = frame->closure->upvalues[index];
                    }
                }
                break;
            }
            case OP_CLOSE_UPVALUE:
                closeUpvalues(vm.stackTop - 1);
                pop();
                break;
            case OP_RETURN: {
                // holding onto the return value of the function
                Value result = pop();
                closeUpvalues(frame->slots);
                vm.frameCount--;
                if (vm.frameCount == 0) {
                    pop();
                    return INTERPRET_OK;
                }
                vm.stackTop = frame->slots;
                push(result); // pushing the return value back onto the stack
                frame = &vm.frames[vm.frameCount-1];
                break;
            }
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_STRING
#undef READ_SHORT
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    ObjFunction* function = compile(source);
    if (function == NULL) return INTERPRET_COMPILE_ERROR;

    push(OBJ_VAL(function));
    ObjClosure* closure = newClosure(function);
    pop();
    push(OBJ_VAL(closure));
    call(closure, 0);

    return run();
}
