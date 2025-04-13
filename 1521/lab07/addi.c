// generate the encoded binary for an addi instruction, including opcode and operands

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the encoded binary MIPS for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    uint32_t opcode = 0x8;
    uint32_t encoded = (opcode << 26)
                    | ((s & 0x1F) << 21)
                    | ((t & 0x1F) << 16)
                    | ((i & 0xFFFF));

    return encoded; // REPLACE WITH YOUR CODE

}
