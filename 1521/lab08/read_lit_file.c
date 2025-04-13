#include <stdio.h>
#include <stdint.h>

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

  char number[3];
  if (fread(number, 1, 3, f) != 3 || number[0] != 0x4C || number[1] != 0x49 || number[2] != 0x54) {
      fprintf(stderr, "Failed to read\n");
      fclose(f);
      return 1;
  }

  int c;
  while ((c = fgetc(f)) != EOF) {
      if (c < '1' || c > '8') {
          fprintf(stderr, "Invalid record \n");
          fclose(f);
          return 1;
      }

      char b[8];
      if (fread(b, 1, c - '0', f) != c - '0') {
          fprintf(stderr, "Failed to read\n");
          fclose(f);
          return 1;
      }

      uint64_t v = 0;
      for (int i = c - '0' - 1; i >= 0; i--) {
          v <<= 8;
          v |= ((int)b[i] & 0xFF);
      }

      printf("%lu\n", v);
  }
  fclose(f);
  return 0;
}