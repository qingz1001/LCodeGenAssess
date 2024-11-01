#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 500005
#define INF 1e20

typedef struct {
    long long x;
    long long r;
    long long v;
} Station;

Station stations[MAXN];
double dp[MAXN];

int compare(const void *a, const void *b) {
    return ((Station *)a)->x - ((Station *)b)->x;
}

int main() {
    int n;
    long long m;
    scanf("%d %lld", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &stations[i].x, &stations[i].r, &stations[i].v);
    }

    qsort(stations, n, sizeof(Station), compare);

    for (int i = 0; i < n; i++) {
        dp[i] = INF;
    }

    dp[0] = stations[0].v;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            double dist = sqrt((stations[i].x - stations[j].x) * (stations[i].x - stations[j].x) + 4 * stations[j].r);
            if (dist <= stations[i].r) {
                dp[i] = fmin(dp[i], dp[j] + stations[i].v + sqrt(stations[i].r));
            }
        }
    }

    double min_cost = INF;
    for (int i = 0; i < n; i++) {
        double dist = sqrt((m - stations[i].x) * (m - stations[i].x) + 4 * stations[i].r);
        if (dist <= stations[i].r) {
            min_cost = fmin(min_cost, dp[i] + sqrt(stations[i].r));
        }
    }

    printf("%.3f\n", min_cost);

    return 0;
}