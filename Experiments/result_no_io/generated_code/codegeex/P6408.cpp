#include <stdio.h>

int main() {
    int scores[5] = {0, 0, 0, 0, 0}; // 初始化5个选手的分数

    // 读取输入
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            int rating;
            scanf("%d", &rating);
            scores[i] += rating; // 累加每位选手的评分
        }
    }

    // 找出分数最高的选手
    int max_score = scores[0];
    int max_index = 0;
    for (int i = 1; i < 5; i++) {
        if (scores[i] > max_score) {
            max_score = scores[i];
            max_index = i;
        }
    }

    // 输出结果
    printf("%d %d\n", max_index + 1, max_score); // 选手编号从1开始

    return 0;
}