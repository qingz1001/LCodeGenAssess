#include <stdio.h>

typedef unsigned long long ull;

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        ull l, r;
        scanf("%llu %llu", &l, &r);
        ull count = ( (r +1) /2 ) - (l /2);
        printf("%llu\n", count);
    }
    return 0;
}