#include <stdio.h>
#include <string.h>

int main() {
    int x1, y1, x2, y2, T;
    char wind[51];
    int steps = 0;

    // 读取起点和终点坐标
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    scanf("%d", &T);
    getchar(); // 读取换行符

    // 如果起点和终点相同，直接输出0步
    if (x1 == x2 && y1 == y2) {
        printf("0\n");
        return 0;
    }

    // 遍历每个时刻的风向
    for (int i = 0; i < T; i++) {
        scanf("%c", &wind[i]);
        getchar(); // 读取换行符

        // 根据风向更新坐标
        if (wind[i] == 'E' && x1 < x2) {
            x1++;
        } else if (wind[i] == 'W' && x1 > x2) {
            x1--;
        } else if (wind[i] == 'N' && y1 < y2) {
            y1++;
        } else if (wind[i] == 'S' && y1 > y2) {
            y1--;
        }

        // 如果到达终点，输出步数并结束程序
        if (x1 == x2 && y1 == y2) {
            printf("%d\n", steps);
            return 0;
        }
        steps++;
    }

    // 如果遍历完所有时刻仍未到达终点，输出-1
    printf("-1\n");
    return 0;
}