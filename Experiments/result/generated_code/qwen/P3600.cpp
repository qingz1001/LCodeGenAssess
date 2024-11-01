#include <stdio.h>
#include <stdlib.h>

#define MOD 666623333

int main() {
    int n, x, q;
    scanf("%d %d %d", &n, &x, &q);

    // Calculate the expected value for each query
    long long result = 0;
    for (int i = 1; i <= q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        long long min_val = 0;
        for (int j = l; j <= r; j++) {
            min_val += (j == 1) ? 1 : min_val + 1;
        }
        result = (result > min_val) ? result : min_val;
    }

    // Calculate the final result modulo MOD
    long long final_result = 0;
    for (int i = 1; i <= result; i++) {
        final_result = (final_result * result) % MOD;
    }

    printf("%lld\n", final_result);

    return 0;
}