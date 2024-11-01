#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100

typedef struct Node {
    int weight;
    int left;
    int right;
} Node;

Node tree[MAXN + 1];
int n;

int minDistanceSum = INT_MAX;

int calculateDistanceSum(int root, int depth) {
    if (root == 0) return 0;
    int leftSum = calculateDistanceSum(tree[root].left, depth + 1);
    int rightSum = calculateDistanceSum(tree[root].right, depth + 1);
    return tree[root].weight * depth + leftSum + rightSum;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int w, u, v;
        scanf("%d %d %d", &w, &u, &v);
        tree[i].weight = w;
        tree[i].left = u;
        tree[i].right = v;
    }

    for (int i = 1; i <= n; i++) {
        int distanceSum = calculateDistanceSum(i, 0);
        if (distanceSum < minDistanceSum) {
            minDistanceSum = distanceSum;
        }
    }

    printf("%d\n", minDistanceSum);
    return 0;
}