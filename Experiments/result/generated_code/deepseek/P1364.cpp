#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100

typedef struct Node {
    int population;
    int left;
    int right;
} Node;

Node tree[MAXN + 1];
int n;

int min(int a, int b) {
    return a < b ? a : b;
}

int calculateDistance(int root, int parent, int depth) {
    if (root == 0) return 0;
    int left = tree[root].left;
    int right = tree[root].right;
    int population = tree[root].population;
    int distance = population * depth;
    distance += calculateDistance(left, root, depth + 1);
    distance += calculateDistance(right, root, depth + 1);
    return distance;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int w, u, v;
        scanf("%d %d %d", &w, &u, &v);
        tree[i].population = w;
        tree[i].left = u;
        tree[i].right = v;
    }

    int minDistance = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int distance = calculateDistance(i, -1, 0);
        minDistance = min(minDistance, distance);
    }

    printf("%d\n", minDistance);
    return 0;
}