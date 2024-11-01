#include <stdio.h>

int main() {
    int M, S, T;
    scanf("%d%d%d", &M, &S, &T);

    int max_distance = 0;
    int time = 0;

    while (time < T) {
        if (M >= 10) {
            // 使用闪烁法术
            M -= 10;
            time++;
            if (S <= 60) {
                printf("Yes\n%d\n", time);
                return 0;
            }
            S -= 60;
        } else {
            // 休息恢复魔法值
            int rest_time = (10 - M) / 4;
            if ((10 - M) % 4 != 0) rest_time++;
            if (time + rest_time >= T) {
                // 如果休息时间超过T，则计算能走的最大距离
                max_distance = S + 17 * (T - time);
                printf("No\n%d\n", max_distance);
                return 0;
            }
            M += rest_time * 4;
            time += rest_time;
        }
    }

    // 如果在T时间内无法逃离荒岛，则计算能走的最大距离
    max_distance = S + 17 * T;
    printf("No\n%d\n", max_distance);

    return 0;
}