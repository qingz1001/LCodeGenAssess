#include <stdio.h>

#define MAX_L 10001

int main() {
    int l, m;
    int road[MAX_L] = {0};
    int i, j, start, end, count = 0;

    scanf("%d %d", &l, &m);

    // 初始化道路，所有位置都有树
    for (i = 0; i <= l; i++) {
        road[i] = 1;
    }

    // 处理每个区域
    for (i = 0; i < m; i++) {
        scanf("%d %d", &start, &end);
        // 将区域内的树移除
        for (j = start; j <= end; j++) {
            road[j] = 0;
        }
    }

    // 计算剩余的树
    for (i = 0; i <= l; i++) {
        if (road[i] == 1) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}