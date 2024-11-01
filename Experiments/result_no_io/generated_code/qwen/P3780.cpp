#include <stdio.h>
#include <stdlib.h>

#define MAXN 20005
#define MAXK 500001

typedef struct Node {
    int parent;
    int apples;
    int happiness;
} Node;

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int node, int depth, int *maxDepth, long long *totalHappiness, long long *maxHappiness, int *taken, Node *nodes) {
    if (node == 0) {
        return;
    }

    taken[node] = 1;
    *maxDepth = max(*maxDepth, depth);

    for (int i = 1; i <= nodes[node].apples; ++i) {
        totalHappiness[i] += nodes[node].happiness * i;
        maxHappiness[i] = max(maxHappiness[i], totalHappiness[i]);
    }

    for (int child = 1; child <= nodes[node].apples; ++child) {
        dfs(nodes[node].parent, depth + 1, maxDepth, totalHappiness, maxHappiness, taken, nodes);
    }

    for (int i = 1; i <= nodes[node].apples; ++i) {
        totalHappiness[i] -= nodes[node].happiness * i;
        maxHappiness[i] = max(maxHappiness[i], totalHappiness[i]);
    }
}

int main() {
    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int n, k;
        scanf("%d %d", &n, &k);

        Node nodes[MAXN];
        for (int i = 1; i <= n; ++i) {
            scanf("%d %d %d", &nodes[i].parent, &nodes[i].apples, &nodes[i].happiness);
        }

        int maxDepth = 0;
        long long totalHappiness[MAXK + 1] = {0};
        long long maxHappiness[MAXK + 1] = {0};
        int taken[MAXN] = {0};

        dfs(1, 1, &maxDepth, totalHappiness, maxHappiness, taken, nodes);

        int result = 0;
        for (int i = 1; i <= nodes[1].apples; ++i) {
            if (i - maxDepth <= k) {
                result = max(result, maxHappiness[i]);
            }
        }

        printf("%d\n", result);
    }

    return 0;
}