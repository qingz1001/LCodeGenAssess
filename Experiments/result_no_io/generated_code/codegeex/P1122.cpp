#include <stdio.h>
#include <stdlib.h>

#define MAXN 16000

int n;
int adj[MAXN][MAXN]; // 邻接矩阵表示图
int beauty[MAXN]; // 存储每朵花的美丽指数

// 深度优先搜索计算最大子树和
int dfs(int node, int parent) {
    int maxSubtreeSum = 0;
    for (int i = 0; i < n; i++) {
        if (adj[node][i] && i != parent) {
            maxSubtreeSum = (maxSubtreeSum > 0) ? maxSubtreeSum : 0;
            int subtreeSum = dfs(i, node) + beauty[i];
            maxSubtreeSum = (subtreeSum > maxSubtreeSum) ? subtreeSum : maxSubtreeSum;
        }
    }
    return maxSubtreeSum;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &beauty[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    int maxSum = 0;
    for (int i = 0; i < n; i++) {
        int currentSum = dfs(i, -1) + beauty[i];
        maxSum = (currentSum > maxSum) ? currentSum : maxSum;
    }

    printf("%d\n", maxSum);
    return 0;
}