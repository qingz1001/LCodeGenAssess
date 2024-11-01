#include <stdio.h>
#include <stdbool.h>

#define MOD 11192869
#define MAXN 3
#define MAXM 50

int n, m;
int T[MAXN][MAXM];
int L[MAXN * MAXM];
int dp[MAXN][MAXM][1 << (MAXN * MAXM)];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int dfs(int x, int y, int state) {
    if (state == (1 << (n * m)) - 1) return 1;
    if (dp[x][y][state] != -1) return dp[x][y][state];

    int res = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
            int idx = nx * m + ny;
            if (!(state & (1 << idx)) && T[nx][ny] == L[__builtin_popcount(state)]) {
                res = (res + dfs(nx, ny, state | (1 << idx))) % MOD;
            }
        }
    }
    dp[x][y][state] = res;
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &T[i][j]);
        }
    }
    for (int i = 0; i < n * m; i++) {
        scanf("%d", &L[i]);
    }

    int total = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i == 0 || i == n - 1 || j == 0 || j == m - 1) && T[i][j] == L[0]) {
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < m; y++) {
                        for (int s = 0; s < (1 << (n * m)); s++) {
                            dp[x][y][s] = -1;
                        }
                    }
                }
                total = (total + dfs(i, j, 1 << (i * m + j))) % MOD;
            }
        }
    }

    printf("%d\n", total);
    return 0;
}