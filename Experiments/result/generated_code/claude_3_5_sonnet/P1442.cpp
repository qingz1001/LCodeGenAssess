#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define INF 1000000000

typedef long long ll;

struct Platform {
    int h, l, r;
};

struct Platform platforms[MAX_N];
int n, h;
ll x, y;
ll dp[MAX_N];

int cmp(const void *a, const void *b) {
    return ((struct Platform*)b)->h - ((struct Platform*)a)->h;
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll abs(ll a) {
    return a < 0 ? -a : a;
}

int main() {
    scanf("%d %d", &n, &h);
    scanf("%lld %lld", &x, &y);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &platforms[i].h, &platforms[i].l, &platforms[i].r);
    }

    qsort(platforms, n, sizeof(struct Platform), cmp);

    memset(dp, 0x3f, sizeof(dp));
    int pos = 0;
    ll res = INF;

    for (int i = 0; i < n; i++) {
        if (platforms[i].h >= y) continue;
        if (y - platforms[i].h > h) break;

        while (pos < n && platforms[pos].h > platforms[i].h) {
            if (platforms[pos].l <= x && x <= platforms[pos].r) {
                dp[pos] = min(dp[pos], y - platforms[pos].h);
            }
            pos++;
        }

        for (int j = 0; j < pos; j++) {
            if (platforms[j].h <= platforms[i].h + h) {
                ll left = abs(platforms[i].l - platforms[j].l) + abs(platforms[i].l - x);
                ll right = abs(platforms[i].r - platforms[j].r) + abs(platforms[i].r - x);
                dp[i] = min(dp[i], min(left, right) + dp[j] + platforms[j].h - platforms[i].h);
            }
        }

        if (platforms[i].h <= h) {
            res = min(res, dp[i] + platforms[i].h);
        }
    }

    printf("%lld\n", res);
    return 0;
}