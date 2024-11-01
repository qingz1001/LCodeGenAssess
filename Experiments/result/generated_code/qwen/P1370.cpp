#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

int main() {
    int n;
    scanf("%d", &n);
    long long *a = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        long long count = 0;
        for (int j = i; j < n; j++) {
            count = (count + 1) % MOD;
            total = (total + count) % MOD;
        }
    }

    printf("%lld\n", total);

    free(a);
    return 0;
}