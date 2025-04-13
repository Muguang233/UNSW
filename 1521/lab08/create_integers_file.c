#include <stdio.h>

int main(int argc, char *argv[]) {

  if (argc != 4) {
    fprintf(stderr, "Usage: %s <filename> <start> <end>\n", argv[0]);
    return 1;
  }
  char *filename = argv[1];
  int start = atoi(argv[2]);
  int end = atoi(argv[3]);

  FILE *f = fopen(filename, "w");
  if (f == NULL) {
    perror("Error opening file");
    return 1;
  }

  for (int i = start; i <= end; i++) {
    fprintf(f, "%d\n", i);
  }
  fclose(f);
  return 0;
}