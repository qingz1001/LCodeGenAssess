#include <stdio.h>

typedef unsigned long long ull;

int main(){
    ull x, n;
    scanf("%llu %llu", &x, &n);
    ull base = x + 1;
    ull result = 1;
    while(n > 0){
        if(n & 1){
            result *= base;
        }
        base *= base;
        n >>=1;
    }
    printf("%llu\n", result);
    return 0;
}