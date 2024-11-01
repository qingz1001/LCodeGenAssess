#include <stdio.h>
#include <stdlib.h>

#define MAXN 30

int main() {
    int n;
    int M[MAXN][MAXN];
    int weight = 0;

    scanf("%d", &n);

    // 读取矩阵的上三角部分
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &M[i][j]);
            M[j][i] = M[i][j]; // 对称矩阵
        }
    }

    // 计算树的重量
    for (int i = 1; i < n; i++) {
        int min_dist = M[0][i];
        for (int j = 1; j < i; j++) {
            if (M[0][j] + M[j][i] < min_dist) {
                min_dist = M[0][j] + M[j][i];
            }
        }
        weight += min_dist;
    }

    printf("%d\n", weight);

    return 0;
}