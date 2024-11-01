#include <stdio.h>
#include <stdlib.h>

#define MOD 666623333

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void exgcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    int temp = *x;
    *x = *y;
    *y = temp - (a / b) * (*y);
}

int inv(int a, int m) {
    int x, y;
    exgcd(a, m, &x, &y);
    return (x % m + m) % m;
}

int main() {
    int n, x, q;
    scanf("%d %d %d", &n, &x, &q);

    int l[q], r[q];
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }

    int total = 1;
    for (int i = 1; i <= n; i++) {
        total = (total * x) % MOD;
    }

    int ans = 0;
    for (int i = 0; i < q; i++) {
        int length = r[i] - l[i] + 1;
        int min_val = 1;
        for (int j = 1; j <= length; j++) {
            min_val = (min_val * (x - j + 1)) % MOD;
        }
        int num = inv(min_val, MOD);
        ans = (ans + (long long)num * total) % MOD;
    }

    printf("%d\n", ans);
    return 0;
}