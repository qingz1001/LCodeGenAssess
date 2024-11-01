#include <stdio.h>
#include <string.h>

#define MAXN 301
#define INF 1000000000

int n, W[MAXN], P[MAXN][MAXN];
int min_cost = INF;

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &W[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &P[i][j]);
        }
    }

    // 计算最小开销
    for (int i = 1; i <= n; i++) {
        int cost = W[i]; // 初始化为挖井费用
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                cost += P[i][j]; // 加上连接所有农场的费用
            }
        }
        if (cost < min_cost) {
            min_cost = cost; // 更新最小开销
        }
    }

    // 输出最小开销
    printf("%d\n", min_cost);
    return 0;
}