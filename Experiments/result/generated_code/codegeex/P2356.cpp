#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int grid[n][n];
    int row_sums[n];
    int col_sums[n];

    // 初始化行和列的和
    for (int i = 0; i < n; i++) {
        row_sums[i] = 0;
        col_sums[i] = 0;
    }

    // 读取矩阵并计算每行的和
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
            row_sums[i] += grid[i][j];
            col_sums[j] += grid[i][j];
        }
    }

    int max_score = 0;
    int safe_positions = 0;

    // 遍历每个位置，检查是否可以放置弹珠
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                safe_positions++;
                int score = row_sums[i] + col_sums[j] - grid[i][j];
                if (score > max_score) {
                    max_score = score;
                }
            }
        }
    }

    if (safe_positions == 0) {
        printf("Bad Game!\n");
    } else {
        printf("%d\n", max_score);
    }

    return 0;
}