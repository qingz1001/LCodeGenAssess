#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long power10[19] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,
                                   10000000000,100000000000,1000000000000,10000000000000,
                                   100000000000000,1000000000000000,10000000000000000,
                                   100000000000000000,1000000000000000000};

int main(){
    long long k;
    unsigned long long x;
    scanf("%lld %llu", &k, &x);
    if(k > 18){
        char sx[21];
        sprintf(sx, "%llu", x);
        int len = strlen(sx);
        if(k < len){
            // Not possible since k >18 and len <=18
        }
        printf("1");
        for(long long i=0;i<k - len;i++) printf("0");
        printf("%s\n", sx);
    }
    else{
        unsigned long long tenk = (k <=18) ? power10[k] : 0;
        unsigned long long sum = tenk + x;
        printf("%llu\n", sum);
    }
    return 0;
}