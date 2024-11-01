#include <stdio.h>

#define MAX_N 1000
#define MAX_K 10

int main() {
    int n, m, k;
    int platforms[MAX_K];
    int time = 0;
    int current_position = 0;
    int platform_index = 0;

    // 读取输入
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &platforms[i]);
    }

    // 模拟Hikari的跳跃过程
    while (current_position < n) {
        // 检查是否在特殊平台上
        if (platform_index < k && current_position == platforms[platform_index]) {
            m++;
            platform_index++;
        }

        // 跳跃
        current_position += m;
        time++;

        // 如果跳过了终点，就回到终点
        if (current_position > n) {
            current_position = n;
        }
    }

    // 输出结果
    printf("%d\n", time);

    return 0;
}