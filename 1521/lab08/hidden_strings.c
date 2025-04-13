#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[4096];
    int count = 0;
    int c;

    while ((c = fgetc(f)) != EOF) {
        if (isprint(c)) {
            if (count < (int)sizeof(buffer) - 1) {
                buffer[count] = c;
                count++;
            }
        } else {
            if (count >= 4) {
                buffer[count] = '\0';
                printf("%s\n", buffer);
            }
            count = 0;
        }
    }

    if (count >= 4) {
        buffer[count] = '\0';
        printf("%s\n", buffer);
    }

    fclose(f);
    return 0;
}