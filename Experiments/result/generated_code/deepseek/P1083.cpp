#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n, m;
long long r[MAXN], diff[MAXN];

typedef struct {
    int d, s, t;
} Order;

Order orders[MAXN];

int check(int mid) {
    for (int i = 1; i <= n; i++) {
        diff[i] = 0;
    }
    for (int i = 1; i <= mid; i++) {
        diff[orders[i].s] += orders[i].d;
        if (orders[i].t + 1 <= n) {
            diff[orders[i].t + 1] -= orders[i].d;
        }
    }
    long long current = 0;
    for (int i = 1; i <= n; i++) {
        current += diff[i];
        if (current > r[i]) {
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
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &orders[i].d, &orders[i].s, &orders[i].t);
    }

    int left = 1, right = m;
    while (left < right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (check(left)) {
        printf("0\n");
    } else {
        printf("-1\n%d\n", left);
    }

    return 0;
}