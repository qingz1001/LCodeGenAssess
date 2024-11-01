#include <stdio.h>
#include <stdlib.h>

#define MAX_N 6001

int dp[MAX_N][2]; // dp[i][0] 表示不选 i 号职员的的最大快乐值，dp[i][1] 表示选 i 号职员的的最大快乐值
int tree[MAX_N][MAX_N]; // 树的邻接矩阵表示
int happy[MAX_N]; // 职员的快乐值
int n; // 职员数量

// 深度优先搜索
void dfs(int node) {
    dp[node][1] = happy[node]; // 选当前节点
    dp[node][0] = 0; // 不选当前节点

    for (int i = 1; i <= n; i++) {
        if (tree[node][i]) { // 如果 i 是 node 的子节点
            dfs(i); // 先递归计算子节点的值
            dp[node][1] += dp[i][0]; // 选当前节点，则不能选子节点
            dp[node][0] += (dp[i][0] > dp[i][1] ? dp[i][0] : dp[i][1]); // 不选当前节点，则选或不选子节点
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &happy[i]);
        dp[i][0] = dp[i][1] = 0;
    }

    int a, b;
    while (scanf("%d%d", &a, &b) == 2) {
        tree[b][a] = 1; // b 是 a 的直接上司
    }

    dfs(1); // 从根节点开始搜索

    printf("%d\n", (dp[1][0] > dp[1][1] ? dp[1][0] : dp[1][1])); // 输出根节点的最大值

    return 0;
}