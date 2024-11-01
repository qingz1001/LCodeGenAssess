#include <stdio.h>

int main() {
    int n, r;
    scanf("%d %d", &n, &r);

    // 使用杨辉三角来计算组合数
    int C[11][11] = {0};
    for (int i = 0; i <= 10; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    // 计算方案数
    int result = 0;
    for (int i = 0; i <= n - r; i++) {
        result += C[n-1][i] * C[i][r-1];
    }

    printf("%d\n", result);
    return 0;
}