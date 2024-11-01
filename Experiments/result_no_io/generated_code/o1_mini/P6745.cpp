#include <stdio.h>
#include <string.h>

typedef unsigned long long ull;

int main(){
    long long k;
    ull x;
    scanf("%lld %llu", &k, &x);
    if(k <=18){
        ull t=1;
        for(long long i=0;i<k;i++) t *=10;
        printf("%llu\n", t +x);
    }
    else{
        printf("1");
        for(long long i=0;i<k-18;i++) printf("0");
        printf("%018llu\n", x);
    }
}