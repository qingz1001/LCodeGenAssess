#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 155
#define MAX_M 505

int n, m;
int grid[MAX_N][MAX_M];
int sum[MAX_N][MAX_M];
int dp[MAX_N][MAX_M][MAX_N][MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int getSum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}

int getMaxN(int left, int right) {
    int result = INT_MIN;
    for (int k = 3; k <= right - left + 1; k++) {
        for (int i = left; i <= right - k + 1; i++) {
            int j = i + k - 1;
            int temp = dp[1][i][n][j];
            for (int p = 2; p < k; p++) {
                temp = max(temp, dp[1][i][n][i+p-1] + dp[1][i+p][n][j]);
            }
            result = max(result, temp);
        }
    }
    return result;
}

int getMaxO(int left, int right) {
    int result = INT_MIN;
    for (int i = left; i <= right - 2; i++) {
        for (int j = i + 2; j <= right; j++) {
            for (int p = 1; p <= n - 2; p++) {
                for (int q = p + 2; q <= n; q++) {
                    int outer = getSum(p, i, q, j);
                    int inner = getSum(p+1, i+1, q-1, j-1);
                    result = max(result, outer - inner);
                }
            }
        }
    }
    return result;
}

int getMaxI(int left, int right) {
    int result = INT_MIN;
    for (int i = left; i <= right - 2; i++) {
        for (int j = i + 2; j <= right; j++) {
            for (int p = 1; p <= n - 2; p++) {
                int top = dp[p+2][i][n][j];
                int mid = dp[p+1][i+1][p+1][j-1];
                int bottom = dp[1][i][p][j];
                result = max(result, top + mid + bottom);
            }
        }
    }
    return result;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &grid[n-i+1][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + grid[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int p = i; p <= n; p++) {
                for (int q = j; q <= m; q++) {
                    dp[i][j][p][q] = getSum(i, j, p, q);
                }
            }
        }
    }

    int result = INT_MIN;
    for (int i = 3; i <= m - 9; i++) {
        int N = getMaxN(1, i);
        int O = getMaxO(i+1, i+5);
        int I = getMaxI(i+6, m);
        result = max(result, N + O + I);
    }

    printf("%d\n", result);
    return 0;
}