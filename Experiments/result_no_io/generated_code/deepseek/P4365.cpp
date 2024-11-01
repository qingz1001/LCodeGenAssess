#include <stdio.h>
#include <stdlib.h>

#define MOD 64123

typedef struct {
    int x, y;
} Edge;

int n, k, W;
int *d;
Edge *edges;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    scanf("%d %d %d", &n, &k, &W);
    d = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    edges = (Edge *)malloc((n - 1) * sizeof(Edge));
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &edges[i].x, &edges[i].y);
    }

    // Sort the danger levels
    qsort(d, n, sizeof(int), compare);

    // Calculate the sum of the k-th highest danger levels
    int sum = 0;
    for (int i = n - k; i < n; i++) {
        sum += d[i];
        sum %= MOD;
    }

    printf("%d\n", sum);

    free(d);
    free(edges);
    return 0;
}