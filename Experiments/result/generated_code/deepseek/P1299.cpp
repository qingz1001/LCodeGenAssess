#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 2001 // 因为坐标范围是 -1000 到 1000，所以需要 2001 个格子

int main() {
    int N;
    scanf("%d", &N);

    bool paper[MAX_SIZE][MAX_SIZE] = {false}; // 初始化纸张，所有位置都是 false

    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        // 将坐标转换为数组索引
        x1 += 1000;
        y1 += 1000;
        x2 += 1000;
        y2 += 1000;

        // 切割纸张
        if (x1 == x2) { // 垂直切割
            for (int y = y1; y <= y2; y++) {
                paper[x1][y] = true;
            }
        } else if (y1 == y2) { // 水平切割
            for (int x = x1; x <= x2; x++) {
                paper[x][y1] = true;
            }
        }
    }

    int holes = 0;
    for (int x = 0; x < MAX_SIZE; x++) {
        for (int y = 0; y < MAX_SIZE; y++) {
            if (!paper[x][y]) {
                holes++;
            }
        }
    }

    printf("%d\n", holes);

    return 0;
}