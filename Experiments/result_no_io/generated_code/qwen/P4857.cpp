#include <stdio.h>

int main() {
    long long n, k;
    scanf("%lld %lld", &n, &k);
    long long a[k];
    for (long long i = 0; i < k; ++i) {
        scanf("%lld", &a[i]);
    }

    long long result[k];
    for (long long i = 0; i < k; ++i) {
        result[i] = (n + a[i] - 1) / a[i];
    }

    for (long long i = 0; i < k; ++i) {
        printf("%lld ", result[i]);
    }
    printf("\n");

    return 0;
}