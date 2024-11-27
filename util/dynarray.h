#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t size;
    size_t capacity;
    void** data;
} DynArray;

void init_dynarray(DynArray* dyn_array);

void* element_at(DynArray* dyn_array, size_t index);

void push_back(DynArray* dyn_array, void* value, size_t value_size);

void destroy(DynArray* dyn_array);

bool pop(DynArray* dyn_array, void* value, size_t value_size);
