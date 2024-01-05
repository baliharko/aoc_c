#pragma once

#include "dynarray.h"
#include <stdint.h>

void lines_to_dynarray(const char* filepath, DynArray* dyn_array);

const char* lines_as_contiguous_string(const char* filepath, uint32_t max_len);
