#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int original[n];
    int desired[n];

    // 读取每个同学的期望相邻同学
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        desired[i] = a;
    }

    // 构建初始排列
    for (int i = 0; i < n; i++) {
        original[i] = i + 1;
    }

    // 计算每个同学的期望位置
    int pos[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (original[j] == desired[i]) {
                pos[i] = j;
                break;
            }
        }
    }

    // 计算每个位置的偏差
    int diff[n];
    for (int i = 0; i < n; i++) {
        diff[i] = (pos[i] - i + n) % n;
    }

    // 统计偏差的出现次数
    int count[3] = {0}; // 0: -1, 1: 0, 2: 1
    for (int i = 0; i < n; i++) {
        if (diff[i] == 0) {
            count[1]++;
        } else if (diff[i] == 1) {
            count[2]++;
        } else if (diff[i] == 2) {
            count[2]++;
        } else {
            count[0]++;
        }
    }

    // 判断是否无法实现
    if (count[0] > 0) {
        printf("-1\n");
    } else {
        // 最小代价是2倍的2个偏差为1的同学加上1个偏差为0的同学
        printf("%d\n", 2 * count[2] + count[1]);
    }

    return 0;
}