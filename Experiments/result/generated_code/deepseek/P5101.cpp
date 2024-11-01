#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define MAXM 1000005

int N, M;
int C[MAXN];
int color_count[MAXM];
int dp[MAXN][2];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
        color_count[C[i]]++;
    }

    for (int c = 1; c <= M; c++) {
        if (color_count[c] == 0) {
            printf("0\n");
            continue;
        }

        memset(dp, 0x3f, sizeof(dp));
        dp[0][0] = 0;

        for (int i = 1; i <= N; i++) {
            dp[i][0] = dp[i-1][0] + (C[i] != c);
            dp[i][1] = min(dp[i-1][1] + (C[i] != c), dp[i-1][0]);
        }

        int min_cost = min(dp[N][0], dp[N][1]);
        printf("%d\n", min_cost);
    }

    return 0;
}