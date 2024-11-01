#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 1000

int matrix[MAX_N][MAX_M];
int left[MAX_N][MAX_M], right[MAX_N][MAX_M], up[MAX_N][MAX_M], down[MAX_N][MAX_M];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(up, 0, sizeof(up));
    memset(down, 0, sizeof(down));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0 || matrix[i][j] != matrix[i][j-1]) {
                left[i][j] = 0;
            } else {
                left[i][j] = left[i][j-1] + 1;
            }
        }
        for (int j = m-1; j >= 0; j--) {
            if (j == m-1 || matrix[i][j] != matrix[i][j+1]) {
                right[i][j] = 0;
            } else {
                right[i][j] = right[i][j+1] + 1;
            }
        }
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (i == 0 || matrix[i][j] != matrix[i-1][j]) {
                up[i][j] = 0;
            } else {
                up[i][j] = up[i-1][j] + 1;
            }
        }
        for (int i = n-1; i >= 0; i--) {
            if (i == n-1 || matrix[i][j] != matrix[i+1][j]) {
                down[i][j] = 0;
            } else {
                down[i][j] = down[i+1][j] + 1;
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int size = min(min(left[i][j], right[i][j]), min(up[i][j], down[i][j]));
            ans += size + 1;
        }
    }

    printf("%lld\n", ans);

    return 0;
}