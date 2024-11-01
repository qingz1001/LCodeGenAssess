#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int water[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &water[i]);
    }

    int min_tank[m]; // 记录每个水龙头当前的水量
    for (int i = 0; i < m; i++) {
        min_tank[i] = water[i];
    }

    int total_time = 0;
    int idx = m; // 当前正在接水的同学索引

    while (idx < n) {
        int min = min_tank[0];
        int min_idx = 0;
        // 找到当前接水时间最短的龙头
        for (int i = 1; i < m; i++) {
            if (min_tank[i] < min) {
                min = min_tank[i];
                min_idx = i;
            }
        }
        // 将该龙头的时间增加1
        min_tank[min_idx]++;
        // 如果该龙头的时间等于当前同学的时间，则更新接水时间
        if (min_tank[min_idx] == water[idx]) {
            min_tank[min_idx] = 0;
            idx++;
        }
        // 更新总时间
        total_time++;
    }

    // 最后可能还有同学在接水，找出最晚结束的同学的时间
    for (int i = 0; i < m; i++) {
        if (min_tank[i] > total_time) {
            total_time = min_tank[i];
        }
    }

    printf("%d\n", total_time);
    return 0;
}