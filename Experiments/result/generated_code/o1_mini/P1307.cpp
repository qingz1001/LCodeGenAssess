#include <stdio.h>

int main(){
    long long N, absN, reversed = 0;
    scanf("%lld", &N);
    absN = N < 0 ? -N : N;
    if(absN == 0){
        printf("0");
        return 0;
    }
    while(absN > 0){
        reversed = reversed * 10 + (absN % 10);
        absN /= 10;
    }
    if(N < 0){
        reversed = -reversed;
    }
    printf("%lld", reversed);
    return 0;
}