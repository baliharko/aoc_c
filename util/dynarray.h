#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t size;
    size_t capacity;
    void** data;
} DynArray;

void init_dynarray(DynArray* vector);

void* element_at(DynArray* vector, size_t index);

void push_back(DynArray* vector, void* value, size_t value_size);

void destroy(DynArray* vector);
