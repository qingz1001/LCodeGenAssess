#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

long long a[500001], b[500001];
long long A[500001][500001];

int main() {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
    }

    // Construct matrix A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            A[i][j] = a[i] * b[j];
        }
    }

    // Initialize B matrix with a simple pattern
    int B[500001][500001];
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < t; j++) {
            B[i][j] = (i + j) % m + 1;
        }
    }

    // Calculate f(B)
    long long fB = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t; j++) {
            int min_val = B[i][j] < B[i + 1][j] ? B[i][j] : B[i + 1][j];
            int max_val = B[i][j] > B[i + 1][j] ? B[i][j] : B[i + 1][j];
            for (int k = min_val; k <= max_val; k++) {
                fB = (fB + A[i][k - 1]) % MOD;
            }
        }
    }

    printf("%lld\n", fB);

    return 0;
}