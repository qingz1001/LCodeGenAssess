#include <stdio.h>
#include <stdlib.h>

#define MOD 65521

typedef long long ll;

ll determinant(ll **matrix, int n) {
    ll det = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (matrix[j][i] != 0) {
                ll ratio = matrix[i][i] / matrix[j][i];
                for (int k = i; k < n; k++) {
                    matrix[i][k] = (matrix[i][k] - ratio * matrix[j][k] % MOD + MOD) % MOD;
                    ll temp = matrix[i][k];
                    matrix[i][k] = matrix[j][k];
                    matrix[j][k] = temp;
                }
                det = -det;
            }
        }
        if (matrix[i][i] == 0) return 0;
        det = (det * matrix[i][i]) % MOD;
    }
    return (det + MOD) % MOD;
}

int main() {
    int k, n;
    scanf("%d %d", &k, &n);

    ll **matrix = (ll **)malloc(n * sizeof(ll *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (ll *)malloc(n * sizeof(ll));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        matrix[i][i] = k + 1;
        for (int j = 1; j <= k; j++) {
            matrix[i][(i + j) % n] = -1;
            matrix[i][(i - j + n) % n] = -1;
        }
    }

    ll result = determinant(matrix, n - 1);
    printf("%lld\n", result);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}