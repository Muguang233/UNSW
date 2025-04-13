#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv[]) {
    if(argc > 1) {
        int mi = atoi(argv[1]);
        int ma = atoi(argv[1]);
        int sum = 0;
        int prod = 1;
        int mean;
        for(int i = 1; i < argc; i++){
            if(mi > atoi(argv[i])){
                mi = atoi(argv[i]);
            }
            if(ma < atoi(argv[i])){
                ma = atoi(argv[i]);
            }
            sum += atoi(argv[i]);
            prod *= atoi(argv[i]);
            mean = sum/(argc-1);
        }
        printf("MIN:  %d\nMAX:  %d\nSUM:  %d\nPROD: %d\nMEAN: %d\n", mi,ma,sum,prod,mean);
    }
    return 0;
}
