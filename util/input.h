#pragma once

#include "dynarray.h"
#include <stdint.h>

void lines_to_dynarray(const char* filepath, DynArray* dyn_array);

// Removes newline chars
const char* input_as_cont_string(const char* filepath, uint32_t max_len);
