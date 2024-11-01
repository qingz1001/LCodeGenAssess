#include <stdio.h>
#include <string.h>

int n, m, p;
int sum[210][210];
int a[210][210];

int main() {
    // 读取输入
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &sum[i][j]);
        }
    }

    // 初始化第一行和第一列
    for (int i = 1; i <= m; i++) {
        a[1][i] = sum[1][i] - sum[1][i-1];
    }
    for (int i = 1; i <= n; i++) {
        a[i][1] = sum[i][1] - sum[i-1][1];
    }

    // 填充矩阵
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            a[i][j] = sum[i][j] - sum[i-1][j] - sum[i][j-1] + sum[i-1][j-1];
        }
    }

    // 输出结果
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", a[i][j] % p);
        }
        printf("\n");
    }

    return 0;
}