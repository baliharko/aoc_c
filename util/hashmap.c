#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

HashMap *HMCreate(void) {
    HashMap *map = malloc(sizeof(HashMap));    
    map->entries = calloc(MAP_SIZE, sizeof(Entry*));
    return map;
};

uint64_t hash(const void *key, const size_t size) {
    uint64_t out = 666;
    const unsigned char *bytes = (const unsigned char *)key;
    for (unsigned int i = 0; i < size; i++) {
        out = out * 33 + bytes[i];
    }    

    out %= MAP_SIZE;
    return out;
}

Entry *newEntry(const void* key, const size_t keySize, const void* value, const size_t valueSize) {
    Entry *e = malloc(sizeof(Entry));
    e->key = malloc(keySize);
    memcpy(e->key, key, keySize);
    e->keySize = keySize;

    e->value = malloc(valueSize);
    memcpy(e->value, value, valueSize);

    e->next = NULL;
    return e;
}

void HMSet(HashMap *map, const void *key, const size_t keySize, const void *value, const size_t valueSize) {
    uint64_t hashedKey = hash(key, keySize);
    Entry *entry = map->entries[hashedKey];

    if (entry == NULL) {
        map->entries[hashedKey] = newEntry(key, keySize, value, valueSize);
        return;
    }
    
    Entry *prev;
    while (entry != NULL) {
        if (entry->keySize == keySize && memcmp(entry->key, key, keySize) == 0) {
            free(entry->value);
            entry->value = malloc(valueSize);
            memcpy(entry->value, value, valueSize);
            return;
        }

        prev = entry;
        entry = entry->next;
    }

    prev->next = newEntry(key, keySize, value, valueSize);
}

void HMDestroy(HashMap *map) {
    for (int i = 0; i < MAP_SIZE; i++) {
        Entry *entry = map->entries[i];
        while (entry != NULL) {
            Entry *destroy = entry;
            entry = entry->next;
            free(destroy->key);
            free(destroy->value);
            free(destroy);
        }
    }

    free(map->entries);
    free(map);
}

void* HMGet(const HashMap *map, const void *key, const size_t keySize) {
    uint64_t hashedKey = hash(key, keySize);
    Entry *entry = map->entries[hashedKey];
    if (entry == NULL) {
        return NULL;
    }

    while (entry != NULL) {
        if (entry->keySize == keySize && memcmp(entry->key, key, keySize) == 0) {
            return entry->value;
        }

        entry = entry->next;
    }

    return NULL;
}
