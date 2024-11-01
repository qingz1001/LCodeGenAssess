#include <stdio.h>
#include <stdlib.h>

#define MAXN 101
#define INF 0x3f3f3f3f

typedef struct Node {
    int w;       // 结点居民人口数
    int left;    // 左链接
    int right;   // 右链接
} Node;

int n;
Node tree[MAXN];

// 计算从root结点出发，所有结点的距离和
int calculateDistance(int root, int dist) {
    int totalDist = 0;
    if (tree[root].left != 0) {
        totalDist += tree[tree[root].left].w + calculateDistance(tree[root].left, dist + 1);
    }
    if (tree[root].right != 0) {
        totalDist += tree[tree[root].right].w + calculateDistance(tree[root].right, dist + 1);
    }
    return totalDist;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &tree[i].w, &tree[i].left, &tree[i].right);
    }

    int minDistSum = INF;
    for (int i = 1; i <= n; i++) {
        int distSum = calculateDistance(i, 0);
        if (distSum < minDistSum) {
            minDistSum = distSum;
        }
    }

    printf("%d\n", minDistSum);
    return 0;
}