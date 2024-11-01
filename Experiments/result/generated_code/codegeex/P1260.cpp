#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXM 5001

int n, m;
int T[MAXN];

struct Inequality {
    int i, j, b;
} inequalities[MAXM];

int cmp(const void *a, const void *b) {
    struct Inequality *ineqA = (struct Inequality *)a;
    struct Inequality *ineqB = (struct Inequality *)b;
    return ineqA->b - ineqB->b;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &inequalities[i].i, &inequalities[i].j, &inequalities[i].b);
    }

    // Sort inequalities by b
    qsort(inequalities, m, sizeof(struct Inequality), cmp);

    // Initialize T array
    for (int i = 1; i <= n; i++) {
        T[i] = 0;
    }

    // Process inequalities
    for (int i = 0; i < m; i++) {
        int max_diff = inequalities[i].b;
        int j = inequalities[i].j;
        while (j > 0 && T[j] - T[inequalities[i].i] > max_diff) {
            T[j] = T[inequalities[i].i] + max_diff;
            j--;
        }
    }

    // Check if there is a solution
    int min_T = T[1];
    for (int i = 2; i <= n; i++) {
        if (T[i] < min_T) {
            min_T = T[i];
        }
    }

    // Adjust T array so that at least one of the elements is 0
    for (int i = 1; i <= n; i++) {
        T[i] -= min_T;
    }

    // Output the result
    for (int i = 1; i <= n; i++) {
        printf("%d\n", T[i]);
    }

    return 0;
}