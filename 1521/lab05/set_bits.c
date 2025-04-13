#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint32_t set_bits(uint32_t num);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    int num = strtol(argv[1], NULL, 0);
    printf("%d\n", set_bits(num));

    return 0;
}

// return num with the 4th bit set to 0 and
// the 7th bit set to 1
uint32_t set_bits(uint32_t num) {
    // TODO: complete this function
    num &= ~(1 << 4);
    num |= (1 << 7);

    return num;
}
