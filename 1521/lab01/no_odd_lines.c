#include<stdio.h>
#include<string.h>
#define MAX 1024
int main() {
    char str[MAX];
    while(fgets(str, MAX, stdin)!=NULL) {
        int x = strlen(str);
        if(x%2 == 0){
            fputs(str, stdout);
        }
    }


    return 0;
}