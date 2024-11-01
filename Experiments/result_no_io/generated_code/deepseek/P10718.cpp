#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAXN 100005

typedef struct {
    int x, y;
} Point;

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int size;
    int *nodes;
} Cycle;

Point points[MAXN];
Edge edges[MAXN];
Cycle cycles[MAXN];
int n, m, k, q;

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }
    for (int i = 0; i < k; i++) {
        scanf("%d", &cycles[i].size);
        cycles[i].nodes = (int *)malloc(cycles[i].size * sizeof(int));
        for (int j = 0; j < cycles[i].size; j++) {
            scanf("%d", &cycles[i].nodes[j]);
        }
    }
    scanf("%d", &q);
    int z;
    for (int i = 0; i < q; i++) {
        scanf("%d", &z);
        // Placeholder for the actual calculation
        printf("0\n");
    }
    for (int i = 0; i < k; i++) {
        free(cycles[i].nodes);
    }
    return 0;
}