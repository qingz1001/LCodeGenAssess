#include <stdio.h>
#include <stdlib.h>

#define MAXN 6
#define MAXM 6
#define MAX_STATES (1 << (MAXN * MAXM))

int max(int a, int b) {
    return a > b ? a : b;
}

int isValid(int state, int n, int m) {
    for (int i = 0; i < n * m; i++) {
        if (state & (1 << i)) {
            int x = i / m;
            int y = i % m;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                        int ni = nx * m + ny;
                        if (state & (1 << ni)) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        int grid[MAXN][MAXM];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &grid[i][j]);
            }
        }

        int dp[MAX_STATES] = {0};
        int max_sum = 0;

        for (int state = 0; state < (1 << (n * m)); state++) {
            if (!isValid(state, n, m)) continue;
            int sum = 0;
            for (int i = 0; i < n * m; i++) {
                if (state & (1 << i)) {
                    sum += grid[i / m][i % m];
                }
            }
            for (int sub_state = state; sub_state > 0; sub_state = (sub_state - 1) & state) {
                if (isValid(sub_state, n, m)) {
                    dp[state] = max(dp[state], dp[state ^ sub_state] + sum);
                }
            }
            max_sum = max(max_sum, dp[state]);
        }

        printf("%d\n", max_sum);
    }
    return 0;
}