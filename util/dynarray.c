#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

#define INITIAL_CAPACITY 10

void init_dynarray(DynArray* dyn_array) {
    dyn_array->capacity = INITIAL_CAPACITY;
    dyn_array->size = 0;
    dyn_array->data = (void**) malloc(INITIAL_CAPACITY * sizeof(void*));

    for (size_t i = 0; i < dyn_array->capacity; ++i) {
        dyn_array->data[i] = NULL;
    }

    if(dyn_array->data == NULL) {
        printf("Error allocating memory");
    }
}

void* element_at(DynArray* dyn_array, size_t index) {
    if (index >= dyn_array->size || index < 0) {
        printf("Index out of bounds - size: %zu, index: %zu", dyn_array->size, index);
        return NULL;
    }

    return dyn_array->data[index];
}

void push_back(DynArray* dyn_array, void* value, size_t value_size) {
    if (dyn_array->size == dyn_array->capacity) {
        dyn_array->capacity *= 2;
        void** temp_data = (void**) realloc(dyn_array->data, dyn_array->capacity * sizeof(void*));
        if (temp_data == NULL) {
            fprintf(stderr, "Failed to reallocate memory\n");
            exit(EXIT_FAILURE);
        }
        dyn_array->data = temp_data;
    }
    
    dyn_array->data[dyn_array->size] = malloc(value_size);
    memcpy(dyn_array->data[dyn_array->size], value, value_size);
    dyn_array->size++;
}

void destroy(DynArray* dyn_array) {
    for (size_t i = 0; i < dyn_array->size; ++i) {
        free(dyn_array->data[i]);
    }

    free(dyn_array->data);
    dyn_array->size = 0;
    dyn_array->capacity = 0;
}

bool pop(DynArray* dyn_array, void* value, size_t value_size) {
    if (dyn_array == NULL || dyn_array->size == 0) {
        return false;
    }

    void* element = dyn_array->data[dyn_array->size - 1];
    if (element == NULL) {
        return false;
    }

    memcpy(value, element, value_size);
    free(element);
    dyn_array->size--;
    return true;
}
