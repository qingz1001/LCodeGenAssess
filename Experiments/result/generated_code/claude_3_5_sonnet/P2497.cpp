#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 500005
#define INF 1e18

typedef long long ll;

struct Station {
    ll x, r, v;
} s[MAXN];

int n;
ll m;
double dp[MAXN];

double calc(int i, int j) {
    ll dx = s[i].x - s[j].x;
    ll dr = s[i].r + s[j].r;
    return sqrt(dx * dx - dr * dr);
}

int main() {
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld %lld", &s[i].x, &s[i].r, &s[i].v);
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (s[i].x - s[j].x <= s[i].r + s[j].r) continue;
            double cost = dp[j] + s[i].v;
            if (j > 0) cost += sqrt(calc(i, j));
            if (cost < dp[i]) dp[i] = cost;
        }
    }

    double ans = INF;
    for (int i = 1; i <= n; i++) {
        if (m - s[i].x <= s[i].r) {
            if (dp[i] < ans) ans = dp[i];
        }
    }

    printf("%.3f\n", ans);

    return 0;
}