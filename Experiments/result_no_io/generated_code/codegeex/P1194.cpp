#include <stdio.h>
#include <limits.h>

int main() {
    int A, B;
    scanf("%d %d", &A, &B);

    int matrix[B][B];
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // 使用Kruskal算法，构建最小生成树
    int parent[B];
    for (int i = 0; i < B; i++) {
        parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
        }
    }

    int min_cost = B * A; // 初始假设每个物品单独购买，总共花费B * A元
    for (int i = 0; i < B; i++) {
        for (int j = i + 1; j < B; j++) {
            if (matrix[i][j] > 0 && matrix[i][j] < A) {
                int rootI = find(i);
                int rootJ = find(j);
                if (rootI != rootJ) {
                    unionSets(i, j);
                    min_cost += A - matrix[i][j];
                }
            }
        }
    }

    printf("%d\n", min_cost);
    return 0;
}