#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005
#define INF 1e9

int n, k;
long long m[MAXN];

int check(long long p) {
    long long bullets = 0;
    for (int i = 0; i < n; ++i) {
        if (m[i] > 0) {
            long long need = (m[i] + p - 1) / p;
            if (need <= k) {
                bullets += need;
                for (int j = i + 1; j < n && j < i + need; ++j) {
                    m[j] -= p - (j - i) * (j - i);
                }
            } else {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &m[i]);
    }

    long long left = 1, right = INF;
    while (left < right) {
        long long mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", left);

    return 0;
}