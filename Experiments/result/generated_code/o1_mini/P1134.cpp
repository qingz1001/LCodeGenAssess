#include <stdio.h>

int main(){
    unsigned long N;
    scanf("%lu", &N);
    unsigned long long acc = 1;
    for(unsigned long i=1; i<=N; i++){
        acc *= i;
        while(acc % 10 == 0){
            acc /= 10;
        }
        if(acc > 100000000){
            acc %= 100000000;
        }
    }
    printf("%llu\n", acc % 10);
    return 0;
}