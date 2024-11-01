#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化数组并存储双平方数
    int squares[250 * 250 + 1];
    int index = 0;
    for (int p = 0; p <= m; p++) {
        for (int q = 0; q <= m; q++) {
            int square = p * p + q * q;
            squares[index++] = square;
        }
    }

    // 对数组进行排序
    qsort(squares, index, sizeof(int), compare);

    // 查找等差数列
    int count = 0;
    for (int i = 0; i < index - n + 1; i++) {
        int diff = squares[i + 1] - squares[i];
        if (diff == 0) continue; // 避免除以0
        int valid = 1;
        for (int j = 2; j < n; j++) {
            if (squares[i + j] - squares[i + j - 1] != diff) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            count++;
            printf("%d %d\n", squares[i], diff);
        }
    }

    // 如果没有找到任何等差数列，输出NONE
    if (count == 0) {
        printf("NONE\n");
    }

    return 0;
}