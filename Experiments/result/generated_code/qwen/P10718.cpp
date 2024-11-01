#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    // Read coordinates of points
    int *x = (int *)malloc(n * sizeof(int));
    int *y = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    // Read edges
    int **edges = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        edges[i] = (int *)malloc(2 * sizeof(int));
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }

    // Read rings
    int **rings = (int **)malloc(k * sizeof(int *));
    int *ring_sizes = (int *)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        scanf("%d", &ring_sizes[i]);
        rings[i] = (int *)malloc(ring_sizes[i] * sizeof(int));
        for (int j = 0; j < ring_sizes[i]; j++) {
            scanf("%d", &rings[i][j]);
        }
    }

    int q;
    scanf("%d", &q);
    int *queries = (int *)malloc(q * sizeof(int));
    for (int i = 0; i < q; i++) {
        scanf("%d", &queries[i]);
    }

    // Process queries
    for (int i = 0; i < q; i++) {
        int z = queries[i];
        // Calculate f(S) for all subsets S of size z
        // This is a placeholder for the actual computation
        printf("%d\n", 0); // Placeholder output
    }

    // Free allocated memory
    free(x);
    free(y);
    for (int i = 0; i < m; i++) {
        free(edges[i]);
    }
    free(edges);
    for (int i = 0; i < k; i++) {
        free(rings[i]);
    }
    free(rings);
    free(ring_sizes);
    free(queries);

    return 0;
}