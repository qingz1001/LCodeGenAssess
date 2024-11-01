#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MOD 666623333

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int n, x, q;
    scanf("%d %d %d", &n, &x, &q);
    
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % x + 1;
    }
    
    int *queries = (int *)malloc(2 * q * sizeof(int));
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &queries[2 * i], &queries[2 * i + 1]);
    }
    
    int max_min = INT_MIN;
    for (int i = 0; i < q; i++) {
        int l = queries[2 * i] - 1;
        int r = queries[2 * i + 1] - 1;
        int min_val = INT_MAX;
        for (int j = l; j <= r; j++) {
            if (a[j] < min_val) {
                min_val = a[j];
            }
        }
        if (min_val > max_min) {
            max_min = min_val;
        }
    }
    
    long long expected_value = ((long long)max_min * mod_exp(x, MOD - 2, MOD)) % MOD;
    printf("%lld\n", expected_value);
    
    free(a);
    free(queries);
    return 0;
}