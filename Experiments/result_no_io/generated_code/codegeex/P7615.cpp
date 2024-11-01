#include <stdio.h>

int main() {
    int R, C;
    scanf("%d%d", &R, &C);
    char map[R][C + 1]; // 读取地图

    // 读取地图数据
    for (int i = 0; i < R; i++) {
        scanf("%s", map[i]);
    }

    // 遍历地图，检查每个格子是否为死胡同
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == '.') { // 只检查能走的格子
                int count = 0;
                if (i > 0 && map[i - 1][j] == '.') count++;
                if (i < R - 1 && map[i + 1][j] == '.') count++;
                if (j > 0 && map[i][j - 1] == '.') count++;
                if (j < C - 1 && map[i][j + 1] == '.') count++;
                if (count == 1) {
                    printf("1");
                    return 0;
                }
            }
        }
    }

    printf("0");
    return 0;
}