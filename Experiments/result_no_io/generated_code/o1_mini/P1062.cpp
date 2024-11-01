#include <stdio.h>

typedef unsigned long long ull;

int main(){
    int k, N;
    scanf("%d %d", &k, &N);
    ull result = 0;
    int i = 0;
    while(N > 0){
        if(N & 1){
            ull power = 1;
            for(int j=0; j<i; j++) power *= k;
            result += power;
        }
        N >>=1;
        i++;
    }
    printf("%llu", result);
    return 0;
}