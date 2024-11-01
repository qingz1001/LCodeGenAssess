#include <stdio.h>

// 辗转相除法求最大公约数
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int N, m1, m2;
    scanf("%d %d %d", &N, &m1, &m2);

    // 计算 M = m1^m2
    int M = 1;
    for (int i = 0; i < m2; i++) {
        M *= m1;
    }

    int min_time = -1; // 记录最小时间，初始化为-1

    for (int i = 0; i < N; i++) {
        int Si;
        scanf("%d", &Si);

        int current_time = 0;
        int current_cells = Si;

        // 计算当前细胞经过多少秒可以均分到 M 个试管
        while (current_cells % M != 0) {
            current_cells *= Si;
            current_time++;
        }

        // 更新最小时间
        if (min_time == -1 || current_time < min_time) {
            min_time = current_time;
        }
    }

    printf("%d\n", min_time);
    return 0;
}