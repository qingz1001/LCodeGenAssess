#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005
#define MAXQ 200005

int N, Q;
long long S[MAXN];
int T[MAXQ], L[MAXQ], R[MAXQ];
long long dp[MAXN][2];

void update_dp(int t) {
    for (int i = 1; i <= N; i++) {
        dp[i][t % 2] = dp[i - 1][(t - 1) % 2] > dp[i][(t - 1) % 2] ? dp[i - 1][(t - 1) % 2] : dp[i][(t - 1) % 2];
    }
}

long long calculate_cost(int t, int l, int r) {
    long long cost = 0;
    for (int i = l; i <= r; i++) {
        cost += dp[i][t % 2];
    }
    return cost;
}

int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &S[i]);
        dp[i][0] = S[i];
    }

    for (int j = 0; j < Q; j++) {
        scanf("%d %d %d", &T[j], &L[j], &R[j]);
    }

    for (int j = 0; j < Q; j++) {
        for (int t = 1; t <= T[j]; t++) {
            update_dp(t);
        }
        printf("%lld\n", calculate_cost(T[j], L[j], R[j]));
    }

    return 0;
}