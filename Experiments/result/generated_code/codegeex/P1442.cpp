#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int h, l, r;
} Platform;

int compare(const void *a, const void *b) {
    Platform *platformA = (Platform *)a;
    Platform *platformB = (Platform *)b;
    return platformA->h - platformB->h;
}

int main() {
    int n, h;
    scanf("%d %d", &n, &h);
    Platform platforms[n + 1];
    platforms[n].h = 0; // 地面高度设为0

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &platforms[i].h, &platforms[i].l, &platforms[i].r);
    }

    qsort(platforms, n, sizeof(Platform), compare);

    int x, y;
    scanf("%d %d", &x, &y);

    // 初始化答案为铁球下落到第一个平台的时间
    int ans = abs(y - platforms[0].h);

    // 遍历所有平台，寻找最短时间
    for (int i = 0; i < n; i++) {
        // 如果铁球已经到达地面，停止搜索
        if (platforms[i].h == 0) break;

        // 计算铁球从当前平台落到下一个平台的时间
        int time_to_next_platform = abs(y - platforms[i].h);

        // 更新铁球的位置为下一个平台的高度
        y = platforms[i].h;

        // 检查铁球是否能从当前平台落到下一个平台
        if (time_to_next_platform <= h) {
            // 计算铁球从下一个平台落到地面的时间
            int time_to_ground = abs(x - platforms[i].l) + abs(x - platforms[i].r);
            // 更新答案为最短时间
            ans = time_to_next_platform + time_to_ground;
            break;
        }
    }

    printf("%d\n", ans);
    return 0;
}