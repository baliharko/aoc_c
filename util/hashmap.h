#pragma once

#include <stddef.h>

#define MAP_SIZE 10000000

typedef struct Entry{
    char* key;
    size_t keySize;
    void *value;
    struct Entry *next;
} Entry;


typedef struct {
    Entry **entries;
} HashMap;

HashMap *HMCreate(void);

void HMSet(HashMap *map, const void *key, const size_t keySize, const void* value, const size_t valueSize);

void* HMGet(const HashMap *map, const void *key, const size_t keySize);

void HMDestroy(HashMap *map);
