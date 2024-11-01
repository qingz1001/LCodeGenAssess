#include <stdio.h>

#define MAX_N 20
#define INF 0x3f3f3f3f

int n;
int graph[MAX_N][MAX_N];
int dp[1 << MAX_N][MAX_N];

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
}

int tsp() {
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[1][0] = 0;

    for (int i = 3; i <= n; i++) {
        for (int j = 1; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if ((1 << k) & i) {
                    dp[i][j] = (dp[i][j] < dp[i - (1 << j)][k] + graph[k][j]) ? dp[i][j] : dp[i - (1 << j)][k] + graph[k][j];
                }
            }
        }
    }

    int min_cost = INF;
    for (int i = 1; i < n; i++) {
        min_cost = (min_cost < dp[(1 << n) - 1][i] + graph[i][0]) ? min_cost : dp[(1 << n) - 1][i] + graph[i][0];
    }
    return min_cost;
}

int main() {
    input();
    printf("%d\n", tsp());
    return 0;
}