#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

typedef struct {
    long long x;
    long long s;
} Grid;

Grid grids[MAXN];
long long dp[MAXN];

int cmp(const void *a, const void *b) {
    return ((Grid *)a)->x - ((Grid *)b)->x;
}

int canAchieveScore(int n, int d, long long k, int g) {
    for (int i = 0; i < n; i++) {
        dp[i] = LLONG_MIN;
    }
    dp[0] = grids[0].s;

    for (int i = 0; i < n; i++) {
        if (dp[i] == LLONG_MIN) continue;
        for (int j = i + 1; j < n; j++) {
            long long dist = grids[j].x - grids[i].x;
            if (dist < (d - g > 0 ? d - g : 1) || dist > d + g) continue;
            dp[j] = dp[j] > dp[i] + grids[j].s ? dp[j] : dp[i] + grids[j].s;
            if (dp[j] >= k) return 1;
        }
    }
    return 0;
}

int main() {
    int n, d;
    long long k;
    scanf("%d %d %lld", &n, &d, &k);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &grids[i].x, &grids[i].s);
    }

    qsort(grids, n, sizeof(Grid), cmp);

    int left = 0, right = grids[n - 1].x;
    int result = -1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (canAchieveScore(n, d, k, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", result);
    return 0;
}