#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  if(argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    struct stat s;
    if (stat(argv[i], &s) != 0) {
      perror(argv[i]);
      continue;
    }
    char type;
    if ((s.st_mode & 0170000) == 0040000) {
      type = 'd';
    } else {
      type = '-';
    }
    char perms[10];
    if (s.st_mode & 0400) perms[0] = 'r'; else perms[0] = '-';
    if (s.st_mode & 0200) perms[1] = 'w'; else perms[1] = '-';
    if (s.st_mode & 0100) perms[2] = 'x'; else perms[2] = '-';
    if (s.st_mode & 0040) perms[3] = 'r'; else perms[3] = '-';
    if (s.st_mode & 0020) perms[4] = 'w'; else perms[4] = '-';
    if (s.st_mode & 0010) perms[5] = 'x'; else perms[5] = '-';
    if (s.st_mode & 0004) perms[6] = 'r'; else perms[6] = '-';
    if (s.st_mode & 0002) perms[7] = 'w'; else perms[7] = '-';
    if (s.st_mode & 0001) perms[8] = 'x'; else perms[8] = '-';
    perms[9] = '\0';

    printf("%c%s %s\n", type, perms, argv[i]);

  }

  return 0;
}