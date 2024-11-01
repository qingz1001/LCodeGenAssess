#include <stdio.h>

#define MOD 65521

long long matrix[110][110];
int n, k;

void initializeMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = k - 2;
            } else if (abs(i - j) <= k) {
                matrix[i][j] = -1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}

long long determinant(int size) {
    if (size == 1) {
        return matrix[0][0];
    }
    long long det = 0;
    for (int i = 0; i < size; i++) {
        int subSize = size - 1;
        long long subDet = determinant(subSize);
        if (i % 2 == 0) {
            det = (det + matrix[0][i] * subDet) % MOD;
        } else {
            det = (det - matrix[0][i] * subDet) % MOD;
        }
    }
    return det;
}

int main() {
    int k, n;
    scanf("%d%d", &k, &n);

    initializeMatrix();

    long long result = determinant(n - 1);
    printf("%lld\n", (result + MOD) % MOD);

    return 0;
}