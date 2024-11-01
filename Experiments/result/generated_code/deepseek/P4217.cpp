#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100000

typedef long long ll;

int N;
int D[MAXN], U[MAXN], P[MAXN], M[MAXN], C[MAXN];
ll dp[MAXN][2]; // dp[i][0]表示第i季度不延迟订单的最小费用，dp[i][1]表示第i季度延迟订单的最小费用

ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    FILE *fin = fopen("product.in", "r");
    FILE *fout = fopen("product.out", "w");

    fscanf(fin, "%d", &N);
    for (int i = 0; i < N; i++) fscanf(fin, "%d", &D[i]);
    for (int i = 0; i < N; i++) fscanf(fin, "%d", &U[i]);
    for (int i = 0; i < N; i++) fscanf(fin, "%d", &P[i]);
    for (int i = 0; i < N - 1; i++) fscanf(fin, "%d", &M[i]);
    for (int i = 0; i < N - 1; i++) fscanf(fin, "%d", &C[i]);

    // 初始化
    dp[0][0] = (ll)D[0] * P[0];
    dp[0][1] = (ll)(D[0] - min(D[0], U[0])) * C[0] + (ll)min(D[0], U[0]) * P[0];

    for (int i = 1; i < N; i++) {
        // 不延迟订单
        dp[i][0] = dp[i-1][0] + (ll)D[i] * P[i];
        if (i > 0) dp[i][0] += (ll)(D[i-1] - min(D[i-1], U[i-1])) * M[i-1];

        // 延迟订单
        ll cost_produce = (ll)min(D[i], U[i]) * P[i];
        ll cost_delay = (ll)(D[i] - min(D[i], U[i])) * C[i];
        dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + cost_produce + cost_delay;
        if (i > 0) dp[i][1] += (ll)(D[i-1] - min(D[i-1], U[i-1])) * M[i-1];
    }

    ll result = min(dp[N-1][0], dp[N-1][1]);
    fprintf(fout, "%lld\n", result);

    fclose(fin);
    fclose(fout);
    return 0;
}