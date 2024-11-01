#include <stdio.h>

int main() {
    int scores[5][4];
    int total_scores[5] = {0};
    int max_score = 0;
    int winner = 0;

    // 读取输入并计算总分
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &scores[i][j]);
            total_scores[i] += scores[i][j];
        }
        
        // 更新最高分和获胜者
        if (total_scores[i] > max_score) {
            max_score = total_scores[i];
            winner = i + 1;
        }
    }

    // 输出结果
    printf("%d %d\n", winner, max_score);

    return 0;
}