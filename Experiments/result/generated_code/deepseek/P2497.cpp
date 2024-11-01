#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 500005
#define INF 1e18

typedef long long ll;

typedef struct {
    ll x, r, v;
} Station;

Station stations[MAXN];
double dp[MAXN];

int cmp(const void *a, const void *b) {
    return ((Station *)a)->x - ((Station *)b)->x;
}

int main() {
    int n;
    ll m;
    scanf("%d %lld", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &stations[i].x, &stations[i].r, &stations[i].v);
    }

    qsort(stations, n, sizeof(Station), cmp);

    for (int i = 0; i < n; i++) {
        dp[i] = INF;
    }

    dp[0] = stations[0].v;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            ll dx = stations[i].x - stations[j].x;
            ll rj = stations[j].r;
            ll ri = stations[i].r;
            double cost = sqrt(dx * dx + ri * ri) + stations[i].v;
            dp[i] = fmin(dp[i], dp[j] + cost);
        }
    }

    double min_cost = INF;
    for (int i = 0; i < n; i++) {
        ll dx = m - stations[i].x;
        ll ri = stations[i].r;
        double cost = sqrt(dx * dx + ri * ri);
        min_cost = fmin(min_cost, dp[i] + cost);
    }

    printf("%.3f\n", min_cost);

    return 0;
}