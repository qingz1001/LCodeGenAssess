#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_E 350
#define INF 1000000000

typedef struct {
    int x;
    int f;
    int c;
} Store;

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int K, E, N;
    scanf("%d %d %d", &K, &E, &N);

    Store stores[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &stores[i].x, &stores[i].f, &stores[i].c);
    }

    // dp[i][j] 表示到达位置 i 且拥有 j 份食物的最小花费
    int dp[E + 1][K + 1];
    for (int i = 0; i <= E; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for (int i = 0; i <= E; i++) {
        for (int j = 0; j <= K; j++) {
            if (dp[i][j] == INF) continue;

            // 不在当前位置购买任何食物
            dp[i][j] = min(dp[i][j], dp[i][j]);

            // 在当前位置购买食物
            for (int k = 0; k < N; k++) {
                if (stores[k].x == i && stores[k].f >= j) {
                    int cost = j * stores[k].c;
                    dp[i][j] = min(dp[i][j], cost);
                } else if (stores[k].x > i) {
                    break;
                }
            }
        }
    }

    int result = INF;
    for (int j = 0; j <= K; j++) {
        result = min(result, dp[E][j]);
    }

    printf("%d\n", result);

    return 0;
}