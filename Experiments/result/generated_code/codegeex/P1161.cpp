#include <stdio.h>

int main() {
    int n, t, a;
    int lights[2000001] = {0}; // 初始化所有灯为关

    // 读取操作次数
    scanf("%d", &n);

    // 处理每次操作
    for (int i = 0; i < n; i++) {
        double ai;
        scanf("%lf %d", &ai, &t);

        // 对每次操作中的每盏灯进行处理
        for (int j = 1; j <= t; j++) {
            int index = (int)(ai * j);
            lights[index] = !lights[index]; // 切换灯的状态
        }
    }

    // 找出唯一开着的灯
    for (int i = 1; i <= 2000000; i++) {
        if (lights[i]) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}