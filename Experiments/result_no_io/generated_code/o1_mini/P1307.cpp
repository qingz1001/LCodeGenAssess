#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    if(N == 0){
        printf("0");
        return 0;
    }
    int sign = N < 0 ? -1 : 1;
    long absN = N * sign;
    long reversed = 0;
    while(absN > 0){
        reversed = reversed * 10 + absN % 10;
        absN /= 10;
    }
    printf("%ld", reversed * sign);
    return 0;
}