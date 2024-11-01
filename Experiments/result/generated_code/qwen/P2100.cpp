#include <stdio.h>

#define MOD 100000000

int main() {
    long long n;
    scanf("%lld", &n);
    
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    
    long long a = 1, b = 2, c;
    for (long long i = 3; i <= n; ++i) {
        c = (a + b) % MOD;
        a = b;
        b = c;
    }
    
    printf("%lld\n", b);
    return 0;
}