#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

#define INITIAL_CAPACITY 10

void init_dynarray(DynArray* vector) {
    vector->capacity = INITIAL_CAPACITY;
    vector->size = 0;
    vector->data = (void**) malloc(INITIAL_CAPACITY * sizeof(void*));

    for (size_t i = 0; i < vector->capacity; ++i) {
        vector->data[i] = NULL;
    }

    if(vector->data == NULL) {
        printf("Error allocating memory");
    }
}

void* element_at(DynArray* vector, size_t index) {
    if (index >= vector->size || index < 0) {
        printf("Index out of bounds - size: %zu, index: %zu", vector->size, index);
        return NULL;
    }

    return vector->data[index];
}

void push_back(DynArray* vector, void* value, size_t value_size) {
    if(vector->size == vector->capacity) {
        vector->capacity *= 2;
        vector->data = (void**) realloc(vector->data, vector->capacity * sizeof(void*));
    }
    
    vector->data[vector->size] = malloc(value_size);
    memcpy(vector->data[vector->size], value, value_size);
    vector->size++;
}

void destroy(DynArray* vector) {
    for(size_t i = 0; i < vector->size; ++i) {
        free(vector->data[i]);
    }

    free(vector->data);
    vector->size = 0;
    vector->capacity = 0;
}
