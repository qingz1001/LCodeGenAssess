#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 500000
#define INF 1e18

typedef long long ll;
typedef double db;

struct Station {
    ll x, r, v;
} stations[MAX_N + 1];

int n;
ll m;
db dp[MAX_N + 1];

db calc(int i, int j) {
    if (stations[i].x >= stations[j].x) return INF;
    ll dx = stations[j].x - stations[i].x;
    ll dr = stations[j].r - stations[i].r;
    return sqrt((db)(dx * dx - dr * dr));
}

int main() {
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld%lld", &stations[i].x, &stations[i].r, &stations[i].v);
    }

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        for (int j = 0; j < i; j++) {
            db cost = dp[j] + stations[i].v + calc(j, i);
            if (cost < dp[i]) dp[i] = cost;
        }
    }

    db ans = INF;
    for (int i = 1; i <= n; i++) {
        ll dx = m - stations[i].x;
        if (dx >= stations[i].r) continue;
        db cost = dp[i] + sqrt((db)(stations[i].r * stations[i].r - dx * dx));
        if (cost < ans) ans = cost;
    }

    printf("%.3f\n", ans);
    return 0;
}