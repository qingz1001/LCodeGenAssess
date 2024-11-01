#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义巡逻车结构体
typedef struct {
    int n; // 出发位置
    int T; // 出发时刻（秒）
    int t; // 路上耗费的时间（秒）
} Patrol;

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    return ((Patrol *)a)->n - ((Patrol *)b)->n;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    // 动态分配巡逻车数组
    Patrol *patrols = (Patrol *)malloc(m * sizeof(Patrol));

    // 读取巡逻车信息
    for (int i = 0; i < m; i++) {
        scanf("%d", &patrols[i].n);
        scanf("%d:%d:%d", &patrols[i].T, &patrols[i].T, &patrols[i].T);
        patrols[i].T *= 3600; // 转换为秒
        scanf("%d", &patrols[i].t);
    }

    // 按出发位置排序
    qsort(patrols, m, sizeof(Patrol), cmp);

    // 计算目标车到达第n个关口的最早时间
    int target_time = 6 * 3600; // 6点整，转换为秒

    // 计算目标车到达第n个关口的最早时间
    for (int i = 0; i < m; i++) {
        if (patrols[i].n == n) {
            target_time = patrols[i].T + patrols[i].t;
            break;
        }
    }

    // 计算目标车与巡逻车的相遇次数
    int meet_count = 0;
    for (int i = 0; i < m; i++) {
        if (patrols[i].T + patrols[i].t <= target_time) {
            meet_count++;
        }
    }

    // 输出结果
    printf("%d\n", meet_count);
    printf("%02d:%02d:%02d\n", target_time / 3600, (target_time % 3600) / 60, target_time % 60);

    // 释放内存
    free(patrols);

    return 0;
}