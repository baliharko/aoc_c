#include "common.h"

int is_symbol(const char c) {
    return (c > '9' || c < '0') && c != '.';
}
