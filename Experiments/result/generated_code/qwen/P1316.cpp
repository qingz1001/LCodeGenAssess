#include <stdio.h>
#define MOD 1000000007

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    if (n == 1) {
        printf("1\n");
        return 0;
    }

    long long total = 0;
    for (int i = 1; i <= n; ++i) {
        total = (total * m + m - 1) % MOD;
    }

    printf("%lld\n", total);
    return 0;
}