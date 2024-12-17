#include "math.h"


int64_t mod(int64_t a, int64_t b) {
    int res = a % b;
    if ((res > 0 && b < 0) || (res < 0 && b > 0)) {
        res += b;
    }
    return res;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t tmp = a;
        a = b;
        b = mod(tmp, b);
    } 

    return a;
}

uint64_t lcm(uint64_t a, uint64_t b) {
    return a * b / gcd(a, b);
}

