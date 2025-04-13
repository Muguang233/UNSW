#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
  if(argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  FILE *f = fopen(argv[1], "r");
  if(f == NULL) {
    perror("Error opening file");
    return 1;
  }

  int b;
  int i = 0;
  while((b = fgetc(f)) != EOF) {
    if (isprint(b)) {
      printf("byte %4d: %3d 0x%02x '%c'\n", i, b, b, b);
    } else {
      printf("byte %4d: %3d 0x%02x\n", i, b, b);
    }
    i++;
  }
  fclose(f);
  return 0;
}