#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 800
#define MAXK 15

int n, m, k;
int matrix[MAXN][MAXN];
int dp[MAXN][MAXN][MAXK][2]; // dp[i][j][x][0/1] 表示到达(i, j)时，小a/uim的魔瓶中有x单位魔液的方法数

int main() {
    scanf("%d %d %d", &n, &m, &k);
    k++; // 因为魔液量是0到k，所以k需要加1

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // 初始化
    dp[0][0][matrix[0][0]][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int x = 0; x < k; x++) {
                if (i > 0) {
                    int new_x = (x + matrix[i][j]) % k;
                    dp[i][j][new_x][1] = (dp[i][j][new_x][1] + dp[i-1][j][x][0]) % MOD;
                }
                if (j > 0) {
                    int new_x = (x + matrix[i][j]) % k;
                    dp[i][j][new_x][1] = (dp[i][j][new_x][1] + dp[i][j-1][x][0]) % MOD;
                }
                if (i > 0) {
                    int new_x = (x - matrix[i][j] + k) % k;
                    dp[i][j][new_x][0] = (dp[i][j][new_x][0] + dp[i-1][j][x][1]) % MOD;
                }
                if (j > 0) {
                    int new_x = (x - matrix[i][j] + k) % k;
                    dp[i][j][new_x][0] = (dp[i][j][new_x][0] + dp[i][j-1][x][1]) % MOD;
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result = (result + dp[i][j][0][1]) % MOD;
        }
    }

    printf("%d\n", result);
    return 0;
}