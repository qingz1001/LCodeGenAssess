#include <stdio.h>
#include <string.h>

#define MAXN 151
#define INF 0x3f3f3f3f

int N;
int V[MAXN], A[MAXN];
int dp[MAXN][MAXN][MAXN];
int cnt[MAXN];

void solve() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &V[i]);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        cnt[A[i]]++;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            memset(dp[i][j], 0, sizeof(dp[i][j]));
        }
    }
    for (int i = 1; i <= N; i++) {
        dp[i][i][cnt[A[i]]] = V[cnt[A[i]]];
    }
    for (int len = 2; len <= N; len++) {
        for (int i = 1; i <= N - len + 1; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                for (int m = 1; m <= cnt[A[i]]; m++) {
                    for (int n = 1; n <= cnt[A[j]]; n++) {
                        if (m == 1 && n == 1 && A[i] == A[j] + 1) {
                            dp[i][j][m] = dp[i][j][m] > dp[i][k][m] + dp[k + 1][j][n] + V[cnt[A[i]]] ? dp[i][j][m] : dp[i][k][m] + dp[k + 1][j][n] + V[cnt[A[i]]];
                        } else if (m == 1 && n == 1 && A[i] != A[j] + 1) {
                            dp[i][j][m] = dp[i][j][m] > dp[i][k][m] + dp[k + 1][j][n] + V[cnt[A[j]]] ? dp[i][j][m] : dp[i][k][m] + dp[k + 1][j][n] + V[cnt[A[j]]];
                        } else if (m != 1 && n != 1 && A[i] == A[j] + 1) {
                            dp[i][j][m] = dp[i][j][m] > dp[i][k][m - 1] + dp[k + 1][j][n] + V[cnt[A[i]]] ? dp[i][j][m] : dp[i][k][m - 1] + dp[k + 1][j][n] + V[cnt[A[i]]];
                        } else if (m != 1 && n != 1 && A[i] != A[j] + 1) {
                            dp[i][j][m] = dp[i][j][m] > dp[i][k][m - 1] + dp[k + 1][j][n] + V[cnt[A[j]]] ? dp[i][j][m] : dp[i][k][m - 1] + dp[k + 1][j][n] + V[cnt[A[j]]];
                        }
                    }
                }
            }
        }
    }
    int ans = -INF;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= cnt[A[i]]; j++) {
            ans = ans > dp[1][N][j] ? ans : dp[1][N][j];
        }
    }
    printf("%d\n", ans);
}

int main() {
    solve();
    return 0;
}