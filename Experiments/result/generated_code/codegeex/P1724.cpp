#include <stdio.h>
#include <string.h>

int main() {
    char command[5005];
    int T, n;
    scanf("%s %d", command, &T);
    n = strlen(command);

    int x = 0, y = 0;
    int count[4] = {0}; // 分别记录四种方向的移动次数

    // 统计每种方向的移动次数
    for (int i = 0; i < n; i++) {
        if (command[i] == 'E') count[0]++;
        else if (command[i] == 'S') count[1]++;
        else if (command[i] == 'W') count[2]++;
        else if (command[i] == 'N') count[3]++;
    }

    // 计算T秒后的位置
    for (int i = 0; i < 4; i++) {
        int steps = T / n; // 先完整地走完一轮
        int remaining_steps = T % n; // 剩余的步数

        // 处理完整轮
        x += steps * count[0];
        y += steps * count[3];
        x -= steps * count[2];
        y -= steps * count[1];

        // 处理剩余的步数
        for (int j = 0; j < remaining_steps; j++) {
            if (command[j] == 'E') x++;
            else if (command[j] == 'S') y--;
            else if (command[j] == 'W') x--;
            else if (command[j] == 'N') y++;
        }
    }

    printf("%d %d\n", x, y);
    return 0;
}