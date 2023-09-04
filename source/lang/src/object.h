#ifndef _object_h
#define _object_h

#include "common.h"
#include "chunk.h"
#include "value.h"

/**
 * @brief Macro to extract the type tag
 *
 */
#define OBJ_TYPE(value) ( AS_OBJ(value)->type )

/**
 * @brief Macro to check if a value is of function type
 *
 */ 
#define IS_FUNCTION(value) isObjType(value, OBJ_FUNCTION)

/**
 * @brief Macro to check if a value is of native function type
 *
 */ 
#define IS_NATIVE(value)   isObjType(value, OBJ_NATIVE);

/**
 * @brief Macro to check if a value is of string type
 *
 */ 
#define IS_STRING(value)   isObjType(value, OBJ_STRING)

/**
 * @brief Macro to convert into function object
 *
 */ 
#define AS_FUNCTION(value)       ( (ObjFunction*)AS_OBJ(value) )

/**
 * @brief Macro to convert into a native function object
 *
 */
#define AS_NATIVE(value) \
    ( ((ObjNative*)AS_OBJ(value))->function )

/**
 * @brief Macro to convert into string implementation
 *
 */ 
#define AS_STRING(value)       ( (ObjString*)AS_OBJ(value) )

/**
 * @brief Macro to convert into C-strings
 *
 */ 
#define AS_CSTRING(value)      ( ((ObjString*)AS_OBJ(value))->chars )

/**
 * @brief Type tags
 *
 */
typedef enum {
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_NATIVE,
    OBJ_STRING,
} ObjType;

/**
 * @class Obj
 * @brief Object wrapper to implement struct inheritance
 *
 */
struct Obj {
    ObjType type;
    struct Obj* next;
};

/**
 * @class ObjFunction
 * @brief Defining functions as first class.
 */
typedef struct {
    Obj obj;
    int arity;
    Chunk chunk;
    ObjString* name;
} ObjFunction;

/**
 * @brief Declare NativeFn as a function pointer that has a return type of
 * Value
 *
 */
typedef Value (*NativeFn)(int argCount, Value* args);

/**
 * @class ObjNative
 * @brief Struct to define native functions
 */
typedef struct {
    Obj obj;
    NativeFn function;
} ObjNative;

/**
 * @class ObjString
 * @brief Child struct for string type
 *
 */
struct ObjString{
    Obj obj;
    int length;
    char* chars;
    uint32_t hash;
};

/**
 * @class ObjString
 * @brief Closure-type struct
 *
 */
typedef struct {
    Obj obj;
    ObjFunction* function;
} ObjClosure;

/**
 * @brief Method to create an ObjClosure.
 *
 * @param function The function object to hold.
 * @return ObjClosure* Pointer to an Objclosure struct.
 */
ObjClosure* newClosure(ObjFunction* function);

/**
 * @brief Method to create an ObjFunction.
 *
 * @return ObjFunction* A pointer to a new function object.
 */
ObjFunction* newFunction();

/**
 * @brief Method to create a new native function
 *
 * @param function A pointer to a native function
 * @return ObjNative* A pointer to the native function created
 */
ObjNative* newNative(NativeFn function);

/**
 * @brief Method to create an ObjString given a C-string. Assumes ownership
 * of the new string created.
 *
 * @param chars The C-string representation
 * @param length The number of characters in the string
 * @return ObjString* A pointer to an ObjString
 */
ObjString* takeString(char* chars, int length);

/**
 * @brief Method to copy the C-string into an ObjString. Assumes no ownership
 * of the characters passed in as args.
 *
 * @param chars The C-string representation
 * @param length The number of characters in the string
 * @return ObjString* A pointer to an ObjString
 */
ObjString* copyString(const char* chars, int length);

/**
 * @brief Method to print the values of the object
 *
 * @param value Value to print
 */
void printObject(Value value);

/**
 * @brief Method to check if a given value is of a specified object type
 *
 * @param value Value for which we will check its type
 * @param type The object type being compared
 * @return true if value is of type ObjType
 */
static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
