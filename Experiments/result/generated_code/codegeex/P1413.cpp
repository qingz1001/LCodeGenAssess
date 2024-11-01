#include <stdio.h>

int main() {
    int n, P, t, map[6][100001], count = 0;

    // 读取僵尸数量
    scanf("%d", &n);

    // 初始化地图
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 100001; j++) {
            map[i][j] = 0;
        }
    }

    // 读取每个僵尸的出现时间和所在行，并在地图上标记
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &P, &t);
        map[P-1][t]++;
    }

    // 遍历地图，计算最少需要的坚果数量
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 100001; j++) {
            if (map[i][j] > 0) {
                count++;
                j += 60; // 一个坚果可以消灭一行中的所有僵尸
            }
        }
    }

    // 输出最少需要的坚果数量
    printf("%d\n", count);

    return 0;
}