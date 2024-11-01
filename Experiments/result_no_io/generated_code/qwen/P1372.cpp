#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    
    if (k == 1) {
        printf("1\n");
        return 0;
    }
    
    long long max_gcd = 0;
    for (long long i = 1; i <= n; i++) {
        for (long long j = i + 1; j <= n && j - i <= k; j++) {
            max_gcd = gcd(max_gcd, gcd(i, j));
        }
    }
    
    printf("%lld\n", max_gcd);
    return 0;
}