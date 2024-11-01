#include <stdio.h>
#include <string.h>

#define MAXN 151

int n, ans;
char grid[MAXN][MAXN];
int height[MAXN][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", grid[i] + 1);
    }

    // 计算每个点向上的高度
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == 'W') {
                height[i][j] = height[i - 1][j] + 1;
            }
        }
    }

    // 计算矩形数量
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == 'W') {
                int minHeight = height[i][j];
                for (int k = j; k >= 1 && grid[i][k] == 'W'; k--) {
                    minHeight = fmin(minHeight, height[i][k]);
                    ans += minHeight;
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}