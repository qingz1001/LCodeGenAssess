#include <stdio.h>
#include <stdlib.h>

#define MOD 19940417

typedef struct Node {
    int x;
    int f;
} Node;

int compare(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    return nodeA->x - nodeB->x;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    Node *points = (Node *)malloc(sizeof(Node) * (K + 2));
    points[0].x = 0;
    points[0].f = 0;
    points[K + 1].x = N;
    points[K + 1].f = 0;

    for (int i = 1; i <= K; i++) {
        scanf("%d %d", &points[i].x, &points[i].f);
    }

    qsort(points, K + 2, sizeof(Node), compare);

    long long ans1 = 1;
    long long max_val = 0;

    for (int i = 0; i < K + 1; i++) {
        int x1 = points[i].x;
        int f1 = points[i].f;
        int x2 = points[i + 1].x;
        int f2 = points[i + 1].f;

        if (f1 == 0) {
            int up = (x2 - x1 - 1) / 2;
            int down = (x2 - x1 - 1) / 2;
            ans1 = (ans1 * (up + 1) % MOD) * (down + 1) % MOD;
            max_val += up;
        } else if (f1 == 1) {
            int up = (x2 - x1 - 1) / 2;
            int down = (x2 - x1 - 1) / 2 + 1;
            ans1 = (ans1 * (up + 1) % MOD) * (down + 1) % MOD;
            max_val += up;
        } else if (f1 == -1) {
            int up = (x2 - x1 - 1) / 2 + 1;
            int down = (x2 - x1 - 1) / 2;
            ans1 = (ans1 * (up + 1) % MOD) * (down + 1) % MOD;
            max_val += up;
        }
    }

    printf("%lld %lld\n", ans1, max_val);

    free(points);
    return 0;
}