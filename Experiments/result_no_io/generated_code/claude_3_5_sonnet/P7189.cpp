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

    // 标记每分钟的停车数量
    for (int i = 0; i < 3; i++) {
        for (int j = begin[i]; j < end[i]; j++) {
            timeline[j]++;
        }
    }

    // 计算总费用
    for (int i = 1; i <= MAX_TIME; i++) {
        switch (timeline[i]) {
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