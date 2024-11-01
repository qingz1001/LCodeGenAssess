#include <stdio.h>

int main() {
    int n, m, a[100], i, j, ans = 1, mod = 10007;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) scanf("%d", &a[i]);
    for (i = 0; i < m; i++) {
        for (j = 0; j < a[i]; j++) {
            ans = (ans * (n - j)) % mod;
            ans = (ans * pow(j + 1, mod - 2, mod)) % mod;
        }
        n -= a[i];
    }
    printf("%d\n", ans);
    return 0;
}

int pow(int a, int b, int mod) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}