#include <stdio.h>

int main(int argc, char *argv[]) {
  if(argc < 3) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];
  FILE *f = fopen(filename, "wb");
  if(f == NULL) {
    perror("Error opening file");
    return 1;
  }
  for(int i = 2; i < argc; i++) {
    int value = atoi(argv[i]);

    if (value < 0 || value > 255) {
      fprintf(stderr, "byte value: %s must be between 0 and 255\n", argv[i]);
      fclose(f);
      return 1;
    }
    fputc(value, f);
  }
  fclose(f);
  return 0;
}