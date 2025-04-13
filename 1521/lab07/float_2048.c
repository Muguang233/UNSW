// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    // PUT YOUR CODE HERE
    float_components_t fc = float_bits(f);

    if (is_zero(fc) || is_nan(fc) || is_positive_infinity(fc) || is_negative_infinity(fc)) {
        return f;
    }
    int new_exponent = fc.exponent + 11;
    if (new_exponent >= 0xFF) {
        return (fc.sign << 31) | (0xFF << 23); // return +inf or -inf
    }
    uint32_t result = (fc.sign << 31) | (new_exponent << 23) | fc.fraction;
    return result;
}
