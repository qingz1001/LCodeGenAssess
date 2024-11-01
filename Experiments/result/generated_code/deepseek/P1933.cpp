#include <stdio.h>
#include <stdbool.h>

#define MOD 11192869

int n, m;
int T[3][50];
int L[150];
int dp[3][50][150];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int solve() {
    int total = n * m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i == 0 || i == n - 1 || j == 0 || j == m - 1) && T[i][j] == L[0]) {
                dp[i][j][0] = 1;
            }
        }
    }

    for (int k = 0; k < total - 1; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (dp[i][j][k] > 0) {
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dx[d];
                        int nj = j + dy[d];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m && T[ni][nj] == L[k + 1]) {
                            dp[ni][nj][k + 1] = (dp[ni][nj][k + 1] + dp[i][j][k]) % MOD;
                        }
                    }
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result = (result + dp[i][j][total - 1]) % MOD;
        }
    }

    return result;
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

    int result = solve();
    printf("%d\n", result);

    return 0;
}