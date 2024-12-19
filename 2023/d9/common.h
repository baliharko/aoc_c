#pragma once

#include <stdbool.h>
#include <stddef.h>

#define LINE_MAX 65536

bool all(int arr[], size_t size, int compare) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] != compare) 
            return false;
    }

    return true;
}
