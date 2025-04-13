#include<stdio.h>
#include<string.h>
#define MAX 1024
int main() {
    char str[MAX];
    while(fgets(str, MAX, stdin)!=NULL) {
        int x = strlen(str);
        printf("%d\n", x);
        printf("%d", 55%2);
    }


    return 0;
}