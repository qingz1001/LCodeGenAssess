#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);

    long long *a = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    long long *b = (long long *)malloc(m * sizeof(long long));
    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
    }

    // Construct matrix A
    long long **A = (long long **)malloc(n * sizeof(long long *));
    for (int i = 0; i < n; i++) {
        A[i] = (long long *)malloc(m * sizeof(long long));
        for (int j = 0; j < m; j++) {
            A[i][j] = a[i] * b[j];
        }
    }

    // Initialize matrix B with the smallest possible values
    int **B = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        B[i] = (int *)malloc(t * sizeof(int));
        for (int j = 0; j < t; j++) {
            B[i][j] = (i == 0) ? 1 : (j > 0 && B[i][j - 1] != 1) ? 1 : 2;
        }
    }

    // Calculate f(B)
    long long result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t; j++) {
            for (int k = 1; k <= m; k++) {
                if (B[i][j] >= k && B[i + 1][j] >= k) {
                    result += A[i][k - 1];
                    result %= MOD;
                }
            }
        }
    }

    printf("%lld\n", result);

    // Free allocated memory
    free(a);
    free(b);
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    for (int i = 0; i <= n; i++) {
        free(B[i]);
    }
    free(B);

    return 0;
}