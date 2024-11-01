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
        det = (det * matrix[i][i] % MOD + MOD) % MOD;
        if (det == 0) return 0;
    }
    return det;
}

int main() {
    int k, n;
    scanf("%d %d", &k, &n);

    ll **matrix = (ll **)malloc((n - 1) * sizeof(ll *));
    for (int i = 0; i < n - 1; i++) {
        matrix[i] = (ll *)malloc((n - 1) * sizeof(ll));
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (i == j) {
                matrix[i][j] = 2 * k + 1;
            } else if (abs(i - j) <= k) {
                matrix[i][j] = -1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }

    ll result = determinant(matrix, n - 1);
    printf("%lld\n", result);

    for (int i = 0; i < n - 1; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}