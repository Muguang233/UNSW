// Get bit at a position n

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int get_nth_bit(uint32_t value, int n);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <value> <bit position>\n", argv[0]);
        return 1;
    }

    int position = atoi(argv[1]);
    uint32_t value = atoi(argv[2]);
    printf("The bit at position %d is: %d\n", position, get_nth_bit(value, position));
    return 0;
}

// given a value and a bit position n,
// returns the nth bit of value
int get_nth_bit(uint32_t value, int n) {
    // TODO: complete this function

    return (value >> n) & 1;
}
