#include <stdio.h>
#include <stdlib.h>

int main() {
    int x1, y1, x2, y2, T;
    char wind[51];
    int steps = 0;

    // 读取起点和终点坐标
    scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &T);

    // 遍历每个时刻的风向
    for (int i = 0; i < T; i++) {
        scanf(" %c", &wind[i]);

        // 计算每个方向上的距离差
        int dx = x2 - x1;
        int dy = y2 - y1;

        // 根据风向选择移动方向
        switch (wind[i]) {
            case 'E':
                if (dx > 0) x1++; // 顺风增加x坐标
                break;
            case 'W':
                if (dx < 0) x1--; // 顺风减少x坐标
                break;
            case 'N':
                if (dy > 0) y1++; // 顺风增加y坐标
                break;
            case 'S':
                if (dy < 0) y1--; // 顺风减少y坐标
                break;
        }

        // 如果已经到达终点，结束循环
        if (x1 == x2 && y1 == y2) {
            steps = i + 1;
            break;
        }
    }

    // 输出结果
    if (x1 == x2 && y1 == y2) {
        printf("%d\n", steps);
    } else {
        printf("-1\n");
    }

    return 0;
}