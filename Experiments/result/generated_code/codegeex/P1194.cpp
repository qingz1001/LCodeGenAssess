#include <stdio.h>
#include <limits.h>

#define MAXN 500

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    int K[MAXN][MAXN];
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            scanf("%d", &K[i][j]);
        }
    }

    // 使用Kruskal算法求解最小生成树
    int parent[MAXN];
    for (int i = 0; i < B; i++) {
        parent[i] = i;
    }

    int edges_used = 0;
    int min_cost = 0;

    // 每次选择最小的边，如果形成环则跳过，直到所有点都连接起来
    while (edges_used < B - 1) {
        int min_edge_cost = INT_MAX;
        int u = -1, v = -1;

        // 找到未连接的最小边
        for (int i = 0; i < B; i++) {
            for (int j = 0; j < B; j++) {
                if (i != j && K[i][j] < min_edge_cost) {
                    min_edge_cost = K[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        // 检查是否形成环
        int root_u = u;
        while (parent[root_u] != root_u) {
            root_u = parent[root_u];
        }

        int root_v = v;
        while (parent[root_v] != root_v) {
            root_v = parent[root_v];
        }

        if (root_u != root_v) {
            parent[root_v] = root_u;
            min_cost += min_edge_cost;
            edges_used++;
        }
    }

    // 加上单个商品的价格
    min_cost += A * (B - edges_used);

    printf("%d\n", min_cost);
    return 0;
}