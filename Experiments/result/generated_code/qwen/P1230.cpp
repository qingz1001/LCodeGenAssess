#include <stdio.h>
#include <stdlib.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int *t = (int *)malloc(n * sizeof(int));
    int *w = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    int dp[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }

    int result = dfs(0, 0, t, w, dp, n, m);

    printf("%d\n", result);

    free(t);
    free(w);
    return 0;
}

int dfs(int index, int time, int *t, int *w, int **dp, int n, int money) {
    if (index == n) {
        return money;
    }
    if (dp[index][time] != -1) {
        return dp[index][time];
    }

    int max_money = money;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            if (time + t[i] <= n) {
                max_money = fmax(max_money, dfs(index + 1, time + t[i], t, w, dp, n, money - w[i]));
            } else {
                max_money = fmax(max_money, dfs(index + 1, time + t[i], t, w, dp, n, money));
            }
            visited[i] = 0;
        }
    }

    dp[index][time] = max_money;
    return max_money;
}