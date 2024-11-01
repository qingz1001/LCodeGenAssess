#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 105
#define MAXP 15
#define MAXS (1 << 12)

int n, p, t;
int g[MAXN][MAXN];
int c[MAXN][MAXP];
int w[MAXS];
int dp[MAXN][MAXS];

int main() {
    // 读取村落数和山贼集团部门数量
    scanf("%d%d", &n, &p);
    
    // 读取村落之间的道路
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        g[x][y] = g[y][x] = 1;
    }
    
    // 读取在每个村落建设每个部门的花费
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &c[i][j]);
        }
    }
    
    // 读取集团间相互影响利益的信息条数
    scanf("%d", &t);
    
    // 读取每条信息
    for (int i = 0; i < t; i++) {
        int v, c, x;
        scanf("%d%d", &v, &c);
        for (int j = 0; j < c; j++) {
            scanf("%d", &x);
        }
    }
    
    // 计算每个子集的收益
    for (int i = 0; i < (1 << p); i++) {
        for (int j = 1; j <= n; j++) {
            int s = 0;
            for (int k = 0; k < p; k++) {
                if (i & (1 << k)) {
                    s += c[j][k];
                }
            }
            w[i] += s;
        }
    }
    
    // 动态规划计算最大收益
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << p); j++) {
            for (int k = 0; k < (1 << p); k++) {
                if ((j & k) == k) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j^k] + w[k]);
                }
            }
        }
    }
    
    // 输出最大收益
    printf("%d\n", dp[n][(1 << p) - 1]);
    
    return 0;
}