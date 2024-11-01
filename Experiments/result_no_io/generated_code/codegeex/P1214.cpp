#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    int l = *((int*)a);
    int r = *((int*)b);
    if (l == r) return 0;
    return (l < r) ? -1 : 1;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    // 创建一个大小为(m*m+1)*(m*m+1)的二维数组来存储双平方数
    int **squares = (int**)malloc((m * m + 1) * sizeof(int*));
    for (int i = 0; i <= m * m; i++) {
        squares[i] = (int*)calloc((m * m + 1), sizeof(int));
    }

    // 计算并存储所有双平方数
    for (int p = 0; p <= m; p++) {
        for (int q = 0; q <= m; q++) {
            squares[p * p + q * q][p * p + q * q] = 1;
        }
    }

    // 遍历所有可能的等差数列的起始值和公差
    for (int start = 0; start <= m * m; start++) {
        if (squares[start][start] == 0) continue;
        for (int diff = 1; start + (n - 1) * diff <= m * m; diff++) {
            int valid = 1;
            for (int i = 1; i < n; i++) {
                if (squares[start + i * diff][start + i * diff] == 0) {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                printf("%d %d\n", start, diff);
            }
        }
    }

    // 释放内存
    for (int i = 0; i <= m * m; i++) {
        free(squares[i]);
    }
    free(squares);

    return 0;
}