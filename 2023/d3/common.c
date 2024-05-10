#include "common.h"

int is_symbol(const char c) {
    return (c > '9' || c < '0') && c != '.';
}

int is_digit(const char c) {
    return c >= '0' && c <= '9';
}
