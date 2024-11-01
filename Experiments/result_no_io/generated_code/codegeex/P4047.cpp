#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &points[i].x, &points[i].y);
    }

    // Kruskal算法求最小生成树
    double edge[n * (n - 1) / 2];
    int edgeCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edge[edgeCount++] = dist(points[i], points[j]);
        }
    }
    sort(edge, edge + edgeCount);

    // 贪心算法：选择最小的k-1条边，将图划分为k个连通块
    double result = edge[0];
    for (int i = 1; i < n - k + 1; i++) {
        result = edge[i];
    }

    printf("%.2f\n", result);
    return 0;
}