#include <stdio.h>

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);

    int bomb[100][100] = {0}; // 用于记录轰炸次数的数组

    // 处理每次轰炸
    for (int i = 0; i < x; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for (int j = x1; j <= x2; j++) {
            for (int k = y1; k <= y2; k++) {
                bomb[j][k]++;
            }
        }
    }

    // 处理每个关键点
    for (int i = 0; i < y; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (bomb[x][y] > 0) {
            printf("Y %d %d\n", bomb[x][y], x); // 输出Y表示被轰炸过，然后输出轰炸次数和最后一次轰炸的轮次
        } else {
            printf("N\n"); // 输出N表示没有被轰炸过
        }
    }

    return 0;
}