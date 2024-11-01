#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n, m;
long long r[MAXN], diff[MAXN];

int check(int d, int s, int t) {
    diff[s] += d;
    if (t + 1 <= n) diff[t + 1] -= d;

    long long current = 0;
    for (int i = 1; i <= n; i++) {
        current += diff[i];
        if (current > r[i]) {
            diff[s] -= d;
            if (t + 1 <= n) diff[t + 1] += d;
            return 0;
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &r[i]);
    }

    int d, s, t;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &d, &s, &t);
        if (!check(d, s, t)) {
            printf("-1\n%d\n", i);
            return 0;
        }
    }

    printf("0\n");
    return 0;
}