#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    double e = 1.0;

    for (int i = 0; i < m; ++i) {
        int t;
        scanf("%d", &t);
        if (t == 0) {
            e *= 0.5;
        } else if (t == 1) {
            e *= 0.25;
        } else if (t == 2) {
            e *= 0.5;
        }
    }

    long long result = (long long)(e * (1LL << n)) % MOD;
    printf("%lld\n", result);

    return 0;
}