#include <stdio.h>

#define MAX_TIME 100

int main() {
    int a, b, c;
    int begin[3], end[3];
    int timeline[MAX_TIME + 1] = {0};
    int total_cost = 0;

    // 读取输入
    scanf("%d %d %d", &a, &b, &c);
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &begin[i], &end[i]);
    }

    // 标记每个时间点的车辆数量
    for (int i = 0; i < 3; i++) {
        for (int t = begin[i]; t < end[i]; t++) {
            timeline[t]++;
        }
    }

    // 计算总费用
    for (int t = 1; t <= MAX_TIME; t++) {
        switch (timeline[t]) {
            case 1:
                total_cost += a;
                break;
            case 2:
                total_cost += 2 * b;
                break;
            case 3:
                total_cost += 3 * c;
                break;
        }
    }

    // 输出结果
    printf("%d\n", total_cost);

    return 0;
}