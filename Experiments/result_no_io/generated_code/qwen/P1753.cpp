#include <stdio.h>
#include <stdlib.h>

#define MAXN 2000000

int min(int a, int b) {
    return (a < b) ? a : b;
}

int matrix_chain_order(int p[], int n) {
    int m[MAXN][MAXN];
    int i, j, k, L, q;

    for (i = 1; i <= n; i++)
        m[i][i] = 0;

    for (L = 2; L <= n; L++) {
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    return m[1][n];
}

int main() {
    int n;
    scanf("%d", &n);
    int* p = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    printf("%d\n", matrix_chain_order(p, n));

    free(p);
    return 0;
}