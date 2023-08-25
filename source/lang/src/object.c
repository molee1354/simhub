#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

/**
 * @brief Macro wrapper to allocateObject wrapper. Casts output to type
 *
 */
#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

/**
 * @brief Method to allocate memory for an Obj struct on the heap
 *
 * @param size Size of memory allocation
 * @param type ObjType type of Obj
 * @return Obj* Pointer to an Obj struct
 */
static Obj* allocateObject(size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;

    // inserting the allocated object into the list
    object->next = vm.objects; // setting next of new head to old head
    vm.objects = object; // setting new head to new object
    return object;
}

/**
 * @brief Method to allocate an ObjString
 *
 * @param chars Character array that represents the string
 * @param length Length of character array
 * @return ObjString* Pointer to the ObjString object
 */
static ObjString* allocateString(char* chars, int length) {
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    return string;
}

ObjString* takeString(char* chars, int length) {
    return allocateString(chars, length);
}

ObjString* copyString(const char* chars, int length) {
    char* heapChars = ALLOCATE(char, length+1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length);
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}

