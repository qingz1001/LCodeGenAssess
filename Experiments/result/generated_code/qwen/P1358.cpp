#include <stdio.h>

#define MOD 10007

int factorial(int num) {
    if (num == 0 || num == 1) return 1;
    int result = 1;
    for (int i = 2; i <= num; i++) {
        result = (result * i) % MOD;
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
    }
    
    long long ways = 1;
    for (int i = 0; i < m; i++) {
        ways = (ways * factorial(n)) % MOD;
        for (int j = 0; j < a[i]; j++) {
            ways = (ways * modInverse(factorial(a[j]), MOD - 2)) % MOD;
        }
        n -= a[i];
    }
    
    printf("%lld\n", ways);
    return 0;
}