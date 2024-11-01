#include <stdio.h>

#define MOD 100

int main() {
    int M, P;
    scanf("%d %d", &M, &P);
    
    int A;
    scanf("%d", &A);
    
    int O, S, U;
    scanf("%d %d %d", &O, &S, &U);
    
    long long total = 1;
    for (int i = 0; i <= M; i++) {
        long long sum = 0;
        for (int j = 0; j <= i; j++) {
            sum = (sum + ((long long)O * j * j + (long long)S * j + U)) % MOD;
        }
        total = (total * sum) % MOD;
    }
    
    printf("%lld\n", total);
    
    return 0;
}