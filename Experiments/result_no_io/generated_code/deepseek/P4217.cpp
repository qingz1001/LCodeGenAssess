#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100000

typedef long long ll;

int N;
int D[MAXN], U[MAXN], P[MAXN], M[MAXN], C[MAXN];
ll dp[MAXN][2];

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

    fclose(fin);

    for (int i = 0; i < N; i++) {
        dp[i][0] = dp[i][1] = LLONG_MAX;
    }

    dp[0][0] = (ll)D[0] * P[0];
    dp[0][1] = (ll)D[0] * C[0];

    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= 1; j++) {
            if (dp[i-1][j] == LLONG_MAX) continue;
            ll cost = dp[i-1][j];
            int delay = j ? D[i-1] : 0;

            // Produce as much as possible
            int produce = min(U[i], D[i] + delay);
            ll produce_cost = (ll)produce * P[i];
            ll delay_cost = (ll)(D[i] + delay - produce) * C[i];
            ll store_cost = 0;

            if (i < N - 1) {
                store_cost = (ll)(produce - D[i]) * M[i];
            }

            dp[i][0] = min(dp[i][0], cost + produce_cost + store_cost);
            dp[i][1] = min(dp[i][1], cost + produce_cost + delay_cost);
        }
    }

    ll result = min(dp[N-1][0], dp[N-1][1]);
    fprintf(fout, "%lld\n", result);

    fclose(fout);
    return 0;
}