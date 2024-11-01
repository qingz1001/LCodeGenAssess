#include <stdio.h>
#include <math.h>

int main() {
    long long N;
    scanf("%lld", &N);
    
    long long i;
    for (i = 1; i * i <= N; i++) {
        printf("%lld ", i * i);
    }
    
    return 0;
}