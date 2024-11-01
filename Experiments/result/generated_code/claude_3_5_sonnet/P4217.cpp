#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000
#define INF 1e18

typedef long long ll;

int N;
int D[MAX_N], U[MAX_N], P[MAX_N], M[MAX_N], C[MAX_N];
ll dp[MAX_N][2];

ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    FILE *in = fopen("product.in", "r");
    FILE *out = fopen("product.out", "w");

    fscanf(in, "%d", &N);
    for (int i = 0; i < N; i++) fscanf(in, "%d", &D[i]);
    for (int i = 0; i < N; i++) fscanf(in, "%d", &U[i]);
    for (int i = 0; i < N; i++) fscanf(in, "%d", &P[i]);
    for (int i = 0; i < N-1; i++) fscanf(in, "%d", &M[i]);
    for (int i = 0; i < N-1; i++) fscanf(in, "%d", &C[i]);

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        ll remain = D[i];
        for (int j = 0; j <= U[i] && j <= remain; j++) {
            ll cost = (ll)j * P[i];
            if (i > 0) cost += min(dp[i-1][0], dp[i-1][1]);
            
            if (j == remain) {
                dp[i][0] = min(dp[i][0], cost);
            } else {
                ll delay = remain - j;
                if (i < N-1) {
                    dp[i][1] = min(dp[i][1], cost + delay * C[i]);
                }
            }
        }

        if (i < N-1) {
            dp[i+1][0] = min(dp[i+1][0], dp[i][0] + (ll)U[i] * M[i]);
            dp[i+1][1] = min(dp[i+1][1], dp[i][1]);
        }
    }

    fprintf(out, "%lld\n", min(dp[N-1][0], dp[N-1][1]));

    fclose(in);
    fclose(out);
    return 0;
}