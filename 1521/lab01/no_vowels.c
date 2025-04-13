#include <stdio.h>
#include <string.h>

int cmp(char c);

int main (void) {
    char s;
    while(scanf("%c", &s) != EOF) {
        if(cmp(s)){
            printf("%c", s);
        }
    }
    return 0;
}

int cmp(char c){
    char *str = "aeiouAEIOU";
    int x = strlen(str);
    for(int i = 0; i < x; i++) {
        if(c == str[i]){
            return 0;
        }
    } 
    return 1;
}