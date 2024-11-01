#include <stdio.h>
#include <string.h>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;

int n, m, cost1, cost2, map[25][10005], f[25][10005][6], jump[6], ans[3];

int main() {
    // 读取输入
    scanf("%d%d%d%d", &n, &m, &cost1, &cost2);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    // 初始化
    memset(f, -inf, sizeof(f));
    f[1][1][1] = 0;
    jump[0] = 0;
    for (int i = 1; i <= 5; i++) {
        jump[i] = jump[i - 1] + cost1;
    }

    // 动态规划求解
    for (int k = 1; k <= 5; k++) { // 遍历连跳次数
        for (int i = 1; i <= m; i++) { // 遍历高度
            for (int j = 1; j <= n; j++) { // 遍历长度
                for (int l = 0; l < k; l++) { // 遍历上一级使用的连跳次数
                    if (f[i - 1][j - jump[l]][l] != -inf) {
                        f[i][j][k] = max(f[i][j][k], f[i - 1][j - jump[l]][l] + map[i][j]);
                    }
                    if (j >= jump[k]) {
                        if (f[i - 1][j - jump[k] + 1][k - 1] != -inf) {
                            f[i][j][k] = max(f[i][j][k], f[i - 1][j - jump[k] + 1][k - 1] + map[i][j]);
                        }
                    }
                }
            }
        }
    }

    // 找到最大收益
    int maxn = -inf;
    for (int k = 1; k <= 5; k++) {
        for (int j = 1; j <= n; j++) {
            maxn = max(maxn, f[m][j][k]);
        }
    }

    // 判断是否找到有效解
    if (maxn == -inf) {
        printf("mission failed\n");
    } else {
        // 找到最小连跳数和最小跳跃高度
        for (int k = 1; k <= 5; k++) {
            for (int j = 1; j <= n; j++) {
                if (f[m][j][k] == maxn) {
                    ans[0] = maxn;
                    ans[1] = k;
                    ans[2] = j;
                    break;
                }
            }
        }
        printf("%d %d %d\n", ans[0], ans[1], ans[2]);
    }

    return 0;
}