#include <stdio.h>
#include <stdbool.h>

#define MAXN 1000

int matrix[MAXN][MAXN];
int dp[MAXN][MAXN];

bool isSymmetric(int x, int y, int size, int n, int m) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[x + i][y + j] != matrix[x + size - 1 - i][y + size - 1 - j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int ans = 0;

    for (int size = 1; size <= n && size <= m; size++) {
        for (int i = 0; i <= n - size; i++) {
            for (int j = 0; j <= m - size; j++) {
                if (isSymmetric(i, j, size, n, m)) {
                    ans++;
                }
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}