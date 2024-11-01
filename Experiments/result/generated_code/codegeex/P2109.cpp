#include <stdio.h>

#define MOD 65521

long long det(int n, int k, int matrix[101][101]) {
    long long result = 0;
    int sign = 1;
    int temp[101][101];

    // Calculate determinant using recursive expansion by minors
    for (int j = 0; j < n; j++) {
        int i = 0;
        while (matrix[i][j] == 0 && i < n - 1) i++;
        if (matrix[i][j] == 0) continue;

        // Swap row i and row j
        for (int x = 0; x < n; x++) {
            int temp = matrix[i][x];
            matrix[i][x] = matrix[j][x];
            matrix[j][x] = temp;
        }

        // Calculate minor determinant
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                if (x != i && y != j) {
                    temp[x][y] = matrix[x][y];
                } else {
                    temp[x][y] = 0;
                }
            }
        }

        long long minor = det(n - 1, k, temp);
        result = (result + sign * matrix[j][j] * minor) % MOD;
        sign = -sign;
    }

    return (sign == 1) ? result : MOD - result;
}

int main() {
    int k, n;
    scanf("%d %d", &k, &n);

    int matrix[101][101] = {0};

    // Construct the adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = n - 1;
            } else if (i == (j + 1) % n || i == (j + 2) % n) {
                matrix[i][j] = -1;
            }
        }
    }

    // Calculate the determinant of the matrix
    long long result = det(n, k, matrix);
    printf("%lld\n", result);

    return 0;
}