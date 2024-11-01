#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005
#define MAXM 100005

int n, m, q;
int parent[MAXN], rank[MAXN];
int graph[MAXN][MAXN], query[MAXM][3], result[MAXM];

// 并查集查找
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 并查集合并
void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// 检查两个节点是否在同一个集合中
int connected(int x, int y) {
    return find(x) == find(y);
}

// 深度优先搜索构建图
void dfs(int u, int p) {
    for (int v = 1; v <= n; v++) {
        if (graph[u][v] && u != v && v != p) {
            dfs(v, u);
            unionSets(u, v);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    int idx = 0;
    while (1) {
        int op;
        scanf("%d", &op);
        if (op == -1) {
            break;
        }
        int u, v;
        scanf("%d %d", &u, &v);
        query[idx][0] = op;
        query[idx][1] = u;
        query[idx][2] = v;
        idx++;
    }

    q = idx;

    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        if (parent[i] == i) {
            dfs(i, -1);
        }
    }

    // 处理查询
    for (int i = 0; i < q; i++) {
        if (query[i][0] == 1) {
            int u = query[i][1];
            int v = query[i][2];
            if (connected(u, v)) {
                result[i] = 1;
            } else {
                result[i] = 0;
            }
        } else if (query[i][0] == 0) {
            int u = query[i][1];
            int v = query[i][2];
            graph[u][v] = graph[v][u] = 0;
            if (connected(u, v)) {
                int rootU = find(u);
                int rootV = find(v);
                parent[rootU] = rootV;
            }
        }
    }

    // 输出结果
    for (int i = 0; i < q; i++) {
        if (query[i][0] == 1) {
            printf("%d\n", result[i]);
        }
    }

    return 0;
}