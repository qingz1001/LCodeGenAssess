#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

int n;
char map[305][305];
int s[305][305], up[305][305], down[305][305];
int ans = -1;

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", map[i] + 1);
    }

    // 计算前缀和
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (map[i][j] == '.');
        }
    }

    // 计算每个点向上的最大矩形面积
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == '*') {
                up[i][j] = 0;
            } else {
                up[i][j] = (j > 1 ? up[i][j - 1] : 0) + 1;
            }
        }
    }

    // 计算每个点向下的最大矩形面积
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if (map[i][j] == '*') {
                down[i][j] = 0;
            } else {
                down[i][j] = (j > 1 ? down[i][j + 1] : 0) + 1;
            }
        }
    }

    // 枚举每个点作为8的顶部矩形的右下角
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int topArea = s[i - 1][j - 1] - s[i - 1][j - up[i][j]] - s[i - up[i][j]][j - 1] + s[i - up[i][j]][j - up[i][j]];
            for (int k = i + 1; k <= n; k++) {
                if (map[k][j] == '*') break;
                int bottomArea = s[k][j - 1] - s[k][j - down[k][j]] - s[i][j - 1] + s[i][j - down[k][j]];
                int currentScore = topArea * bottomArea;
                ans = max(ans, currentScore);
            }
        }
    }

    // 输出结果
    printf("%d\n", ans);
    return 0;
}