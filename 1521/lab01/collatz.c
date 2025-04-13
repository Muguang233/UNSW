#include<stdio.h>
#include<stdlib.h>

void Print(int y);
int main(int argc, char *argv[]){
    if(argc>1){
        int x = atoi(argv[1]);
        printf("%d\n", x); 
        Print(x);
    }
    
    
    
    return 0;
}

void Print(int y){
    if(y == 1){
        EOF;
    } else if(y%2 == 0) {
        y /= 2;
        printf("%d\n", y);
        Print(y);
    } else {
        y = (y*3)+1;
        printf("%d\n", y);
        Print(y);
    }
}