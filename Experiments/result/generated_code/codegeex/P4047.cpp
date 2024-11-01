#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 1005

int n, k;
double dis[MAXN][MAXN];
int parent[MAXN];

// 并查集查找
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 并查集合并
void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

// 比较函数，用于排序
int cmp(const void *a, const void *b) {
    double *x = (double *)a;
    double *y = (double *)b;
    return (*x > *y) - (*x < *y);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%lf%lf", &dis[i][j], &dis[j][i]);
        }
    }
    // 按距离从小到大排序
    qsort(dis[1] + 1, n * (n - 1) / 2, sizeof(double), cmp);
    double result = 0;
    for (int i = 1; i <= n * (n - 1) / 2; i++) {
        if (find(1) != find(n)) {
            unite(1, n);
            result = dis[1][n];
        } else {
            break;
        }
    }
    printf("%.2lf\n", result);
    return 0;
}