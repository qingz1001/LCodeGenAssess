#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2001

int n, m;
int matrix[MAX_N][MAX_N];
int left[MAX_N][MAX_N], right[MAX_N][MAX_N], up[MAX_N][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // 计算每个位置可以向左扩展的最大长度
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (matrix[i][j] != matrix[i][j-1]) {
                left[i][j] = left[i][j-1] + 1;
            } else {
                left[i][j] = 1;
            }
        }
    }

    // 计算每个位置可以向右扩展的最大长度
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if (matrix[i][j] != matrix[i][j+1]) {
                right[i][j] = right[i][j+1] + 1;
            } else {
                right[i][j] = 1;
            }
        }
    }

    // 计算每个位置可以向上扩展的最大长度
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (matrix[i][j] != matrix[i-1][j]) {
                up[i][j] = up[i-1][j] + 1;
            } else {
                up[i][j] = 1;
            }
        }
    }

    int max_square = 0, max_rect = 0;

    // 遍历所有位置，计算最大正方形和最大矩形
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int width = min(left[i][j], right[i][j]);
            int height = up[i][j];
            max_square = max(max_square, min(width, height));
            max_rect = max(max_rect, width * height);
        }
    }

    printf("%d\n%d\n", max_square * max_square, max_rect);

    return 0;
}