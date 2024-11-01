#include <stdio.h>

#define MOD 10007

int factorial(int num) {
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
        n -= a[i];
    }
    
    if (n != 0) {
        printf("0\n");
        return 0;
    }
    
    long long result = 1;
    for (int i = 0; i < m; i++) {
        result = (result * factorial(a[i])) % MOD;
    }
    
    printf("%lld\n", result);
    
    return 0;
}