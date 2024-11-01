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

    long long result = 0;
    for (int i = 0; i < n; i++) {
        long long count = 1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] != a[j - 1]) {
                count++;
            }
        }
        result = (result + count) % MOD;
    }

    printf("%lld\n", result);

    free(a);
    return 0;
}