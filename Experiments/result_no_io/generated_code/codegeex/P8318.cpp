#include <stdio.h>

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    long long b[1001];
    for (long long i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
    }

    for (long long i = m; i >= 1; i--) {
        long long k, x, y;
        scanf("%lld %lld %lld", &k, &x, &y);
        if (k == 1) {
            if (x == y) {
                b[x] /= 2;
            } else {
                b[x] -= b[y];
            }
        } else if (k == 2) {
            if (x == y) {
                b[x] = (long long)sqrt(b[x]);
            } else {
                b[x] /= b[y];
            }
        }
    }

    for (long long i = 1; i <= n; i++) {
        printf("%lld ", b[i]);
    }
    return 0;
}