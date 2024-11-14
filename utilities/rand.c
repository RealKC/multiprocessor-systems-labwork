#include "utilities.h"

u32 xorshift32(u32 x)
{
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    return x;
}
