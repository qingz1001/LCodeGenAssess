#include <stdio.h>
#include <string.h>

#define MAXN 100
#define INF 0x3f3f3f3f

int dist[MAXN][MAXN];
int n, p;
int treasures[MAXN];
int dp[1 << 11][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    // 读取区域数量
    scanf("%d", &n);
    
    // 读取区域之间的距离
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    
    // 读取宝藏数量
    scanf("%d", &p);
    
    // 读取宝藏所在的区域编号
    for (int i = 0; i < p; i++) {
        scanf("%d", &treasures[i]);
        treasures[i]--;
    }
    
    // 初始化dp数组
    memset(dp, INF, sizeof(dp));
    
    // 初始状态，从1号区域出发
    dp[1][0] = 0;
    
    // 状态转移
    for (int mask = 1; mask < (1 << p); mask++) {
        for (int i = 0; i < p; i++) {
            if (mask & (1 << i)) {
                for (int j = 0; j < p; j++) {
                    if (!(mask & (1 << j))) {
                        dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + dist[treasures[i]][treasures[j]]);
                    }
                }
            }
        }
    }
    
    // 计算最终结果
    int result = INF;
    for (int i = 0; i < p; i++) {
        result = min(result, dp[(1 << p) - 1][i] + dist[treasures[i]][n - 1]);
    }
    
    // 输出结果
    printf("%d\n", result);
    
    return 0;
}