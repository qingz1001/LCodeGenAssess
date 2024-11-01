#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001
#define MAXM 1000001

int N, M;
int C[MAXN];
int dp[MAXM][MAXM];

void init() {
    for (int i = 0; i <= M; ++i) {
        for (int j = 0; j <= M; ++j) {
            dp[i][j] = INT_MAX;
        }
    }
}

void solve() {
    init();
    dp[0][0] = 0;

    for (int i = 1; i <= N; ++i) {
        int color = C[i - 1];
        for (int j = 0; j <= M; ++j) {
            if (dp[j][color] != INT_MAX) {
                dp[j | color][color] = dp[j][color];
                dp[j][color] += 1;
            }
        }
    }

    for (int i = 1; i <= M; ++i) {
        printf("%d\n", dp[i][i]);
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &C[i]);
    }
    solve();
    return 0;
}