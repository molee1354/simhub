#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"

/**
 * @brief Define the max load of the table to be 3/4 of its capacity
 *
 */
#define TABLE_MAX_LOAD 0.75

void initTable(Table* table) {
    table->count = 0;
    table->capacity = 0;
    table->entries = NULL;
}

void freeTable(Table* table) {
    FREE_ARRAY(Entry, table->entries, table->capacity);
    initTable(table);
}

/**
 * @brief Method to find if the passed in entry already exists
 *
 * @param entries Array of Entry structs to loop through
 * @param capacity The capacity of the current hashmap
 * @param key Target key
 * @return Entry* NULL if entry doesn't exist'
 */
static Entry* findEntry(Entry* entries, int capacity, ObjString* key) {
    uint32_t index = key->hash % capacity;
    Entry* tombstone = NULL;

    for (;;) {
        Entry* entry = &entries[index];
        if (entry->key == NULL) {
            if (IS_NULL(entry->value)) {
                // Empty entry.
                return tombstone != NULL ? tombstone : entry;
            } else {
                // We found a tombstone.
                if (tombstone == NULL) tombstone = entry;
            }
        } else if (entry->key == key) {
            // We found the key.
            return entry;
        }
        // linear probing -> move on to the next available index
        index = (index+1) % capacity;
    }
}

bool tableGet(Table* table, ObjString* key, Value* value) {
    if (table->count == 0) return false;

    Entry* entry = findEntry(table->entries, table->capacity, key);
    if (entry->key == NULL) return false;

    *value = entry->value;
    return true;
}

/**
 * @brief Method to adjust the capacity of the table
 *
 * @param table Table to adjust the capacity
 * @param capacity Target capacity
 */
static void adjustCapacity(Table* table, int capacity) {
    Entry* entries = ALLOCATE(Entry, capacity);
    for (int i=0; i<capacity; i++) {
        entries[i].key = NULL;
        entries[i].value = NULL_VAL;
    }

    // recalculating the count since tombstones are not being copied
    table->count = 0;

    // manually re-inserting every entry into new empty array
    for (int i=0; i<table->capacity; i++) {
        Entry* entry = &table->entries[i];
        if(entry->key == NULL) continue;

        // finding an entry and managing collisions here
        Entry* dest = findEntry(entries, capacity, entry->key);
        dest->key = entry->key;
        dest->value = entry->value;
        table->count++;
    }

    FREE_ARRAY(Entry, table->entries, table->capacity);
    table->entries = entries;
    table->capacity = capacity;
}

bool tableSet(Table* table, ObjString* key, Value value) {
    // Grows the table if need be
    if (table->count+1 > table->capacity * TABLE_MAX_LOAD) {
        int capacity = GROW_CAPACITY(table->capacity);
        adjustCapacity(table, capacity);
    }
    Entry* entry = findEntry(table->entries, table->capacity, key);

    // determines if the key passed in is a new key
    bool isNewKey = entry->key == NULL;

    if (isNewKey && IS_NULL(entry->value)) table->count++;

    entry->key = key;
    entry->value = value;
    return isNewKey;
}

bool tableDelete(Table* table, ObjString* key) {
    if (table->count == 0) return false;

    // Finding the entry
    Entry* entry = findEntry(table->entries, table->capacity, key);

    // Place a tombstone in the entry. Key is 'gone' but not deleted
    entry->key = NULL;
    entry->value = BOOL_VAL(true);

    return true;
}

void tableAddAll(Table* from, Table *to) {
    for (int i=0; i<from->capacity; i++) {
        Entry* entry = &from->entries[i];

        // for a non-empty key in 'from', add it to 'to'
        if (entry->key != NULL) {
            tableSet(to, entry->key, entry->value);
        }
    }
}

ObjString* tableFindString(Table* table, const char* chars, int length, 
                           uint32_t hash) {
    if (table->count == 0) return NULL;

    // the index where the key is found
    uint32_t index = hash % table->capacity;
    for (;;) {
        Entry* entry = &table->entries[index];
        if (entry->key == NULL) {
            // stop if we find an empty non-tombstone entry
            if (IS_NULL(entry->value)) return NULL;

        } else if (entry->key->length == length &&
                entry->key->hash == hash &&
                memcmp(entry->key->chars, chars, length) == 0) {
            // found the key
            return entry->key;
        }
        index = (index+1) % table->capacity;
    }
}
