#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int matrix[n][n];

    // 读取矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int max_score = 0;

    // 遍历每个位置，计算其得分
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) { // 找到空位
                int score = 0;
                // 计算行得分
                for (int k = 0; k < n; k++) {
                    score += matrix[i][k];
                }
                // 计算列得分
                for (int k = 0; k < n; k++) {
                    score += matrix[k][j];
                }
                score -= matrix[i][j]; // 减去当前位置的敌人分数（因为重复加了一次）
                if (score > max_score) {
                    max_score = score;
                }
            }
        }
    }

    if (max_score == 0) {
        printf("Bad Game!\n");
    } else {
        printf("%d\n", max_score);
    }

    return 0;
}