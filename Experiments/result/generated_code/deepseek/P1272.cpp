#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 150

int N, P;
int parent[MAXN + 1];
int size[MAXN + 1];
int dp[MAXN + 1][MAXN + 1];

void dfs(int node) {
    size[node] = 1;
    for (int i = 1; i <= N; i++) {
        if (parent[i] == node) {
            dfs(i);
            size[node] += size[i];
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &N, &P);
    memset(parent, 0, sizeof(parent));
    for (int i = 1; i < N; i++) {
        int I, J;
        scanf("%d %d", &I, &J);
        parent[J] = I;
    }

    dfs(1);

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= N; i++) {
        dp[i][0] = 0;
        dp[i][size[i]] = 1;
    }

    for (int i = N; i >= 1; i--) {
        for (int j = 1; j < size[i]; j++) {
            for (int k = 1; k <= N; k++) {
                if (parent[k] == i) {
                    for (int l = 0; l <= j; l++) {
                        dp[i][j] = min(dp[i][j], dp[i][j - l] + dp[k][l]);
                    }
                }
            }
        }
    }

    int result = dp[1][P];
    for (int i = 2; i <= N; i++) {
        if (size[i] >= P) {
            result = min(result, dp[i][size[i] - P] + 1);
        }
    }

    printf("%d\n", result);

    return 0;
}