#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define INF INT_MAX

int min(int a, int b) {
    return a < b ? a : b;
}

int k(long long n) {
    if (n == 0) return 0;
    int max_base = (int)sqrt(n);
    int result = INF;
    for (int base = max_base; base >= 1; base--) {
        long long square = (long long)base * base;
        if (square > n) continue;
        result = min(result, k(n - square));
    }
    return result == INF ? INF : result + 1;
}

int main() {
    long long n;
    scanf("%lld", &n);

    int k_n = k(n);
    if (k_n == INF) {
        printf("-\n");
        return 0;
    }

    int count = 0;
    for (long long i = 1; i <= n; i++) {
        if (k(i) > k_n) count++;
    }

    printf("%d %d\n", k_n, count);
    return 0;
}