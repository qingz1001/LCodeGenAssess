#include <stdio.h>
#include <stdlib.h>

// 定义并查集结构体
typedef struct {
    int parent;
    int rank;
} UnionFindSet;

// 初始化并查集
void initUnionFindSet(UnionFindSet *uf, int n) {
    for (int i = 0; i < n; i++) {
        uf[i].parent = i;
        uf[i].rank = 0;
    }
}

// 查找根节点并进行路径压缩
int find(UnionFindSet *uf, int x) {
    if (uf[x].parent != x) {
        uf[x].parent = find(uf, uf[x].parent);
    }
    return uf[x].parent;
}

// 合并两个集合
void unionSets(UnionFindSet *uf, int x, int y) {
    int rootX = find(uf, x);
    int rootY = find(uf, y);

    if (rootX != rootY) {
        if (uf[rootX].rank > uf[rootY].rank) {
            uf[rootY].parent = rootX;
        } else if (uf[rootX].rank < uf[rootY].rank) {
            uf[rootX].parent = rootY;
        } else {
            uf[rootY].parent = rootX;
            uf[rootX].rank++;
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    UnionFindSet uf[N];
    initUnionFindSet(uf, N);

    // 存储每条公路的信息
    int x, y, t;
    int minTime = -1;

    // 读取每条公路的信息
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &x, &y, &t);
        // 按照修复时间排序
        if (minTime == -1 || t < minTime) {
            minTime = t;
        }
    }

    // 按照修复时间排序
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &x, &y, &t);
        if (t == minTime) {
            unionSets(uf, x - 1, y - 1);
        }
    }

    // 检查是否所有村庄都连接起来
    int root = find(uf, 0);
    for (int i = 1; i < N; i++) {
        if (find(uf, i) != root) {
            printf("-1\n");
            return 0;
        }
    }

    printf("%d\n", minTime);
    return 0;
}