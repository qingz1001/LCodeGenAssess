#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int min(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int main() {
    int n, m;
    int matrix[MAX_SIZE][MAX_SIZE];
    int dp[MAX_SIZE][MAX_SIZE] = {0};
    int max_side = 0;

    // 读取输入
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // 动态规划
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 1) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
                }
                if (dp[i][j] > max_side) {
                    max_side = dp[i][j];
                }
            }
        }
    }

    // 输出结果
    printf("%d\n", max_side);

    return 0;
}