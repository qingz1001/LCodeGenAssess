#include <stdio.h>
#include <math.h>

int main() {
    unsigned long long N;
    scanf("%llu", &N);
    
    unsigned long long i;
    for (i = 1; i * i <= N; i++) {
        printf("%llu ", i * i);
    }
    
    return 0;
}