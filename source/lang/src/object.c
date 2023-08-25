#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
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
 * @param hash Hash code for the string
 * @return ObjString* Pointer to the ObjString object
 */
static ObjString* allocateString(char* chars, int length, uint32_t hash) {
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    string->hash = hash;

    // we only care about the keys, so values are NULL
    tableSet(&vm.strings, string, NULL_VAL);
    return string;
}

/**
 * @brief Hash function for language implementation
 *
 * @param key the key to hash 
 * @param length the length of the key
 * @return uint32_t Hash code for string
 */
static uint32_t hashString(const char* key, int length) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
}

ObjString* takeString(char* chars, int length) {
    uint32_t hash = hashString(chars, length); // calculate hash code for string
                                               //
    // look for string in string table
    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
    if (interned != NULL) {
        // if found, we free before we return it since this function
        // is the owner and we don't need the string
        FREE_ARRAY(char, chars, length+1);
        return interned;
    }
    return allocateString(chars, length, hash);
}

ObjString* copyString(const char* chars, int length) {
    uint32_t hash = hashString(chars, length);

    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
    if (interned != NULL) return interned;

    char* heapChars = ALLOCATE(char, length+1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length, hash);
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
            break;
    }
}

