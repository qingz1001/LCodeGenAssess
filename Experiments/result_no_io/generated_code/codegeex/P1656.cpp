#include <stdio.h>
#include <stdlib.h>

#define MAXN 151
#define MAXM 5001

int parent[MAXN];

// 查找并查集的根节点
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 合并两个集合
void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    // 读取边并构建并查集
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        unionSets(a, b);
    }

    // 找出所有的 key roads
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (find(i) != find(j)) {
                printf("%d %d\n", i, j);
            }
        }
    }

    return 0;
}