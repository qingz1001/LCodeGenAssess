#include <stdio.h>
#include <string.h>

#define MAXN 151

int n;
char grid[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", grid[i]);
    }

    int result = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'W') {
                dp[i][j] = 1;
                if (i > 0 && j > 0) {
                    dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
                }
                result += dp[i][j];
            }
        }
    }

    printf("%d\n", result);

    return 0;
}