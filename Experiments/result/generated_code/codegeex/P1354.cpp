#include <stdio.h>
#include <math.h>

#define MAX_WALLS 20
#define ROOM_WIDTH 10.0

// 定义墙的结构体
typedef struct {
    double x; // 墙的横坐标
    double a1, b1; // 第一个空缺区间
    double a2, b2; // 第二个空缺区间
} Wall;

int main() {
    int n;
    scanf("%d", &n);
    Wall walls[MAX_WALLS];
    double distances[MAX_WALLS + 2]; // 0: 起点, n+1: 终点

    // 初始化起点和终点
    distances[0] = 0.0;
    distances[n + 1] = ROOM_WIDTH;

    // 读取墙的信息
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf %lf", &walls[i].x, &walls[i].a1, &walls[i].b1, &walls[i].a2, &walls[i].b2);
        distances[i + 1] = walls[i].x;
    }

    // 计算每个墙之间的最短距离
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n + 1; j++) {
            double min_distance = distances[j] - distances[i];
            for (int k = i + 1; k < j; k++) {
                if (walls[k - 1].a1 <= distances[i] && distances[i] <= walls[k - 1].b1) {
                    min_distance = fmin(min_distance, walls[k - 1].a1 - distances[i]);
                }
                if (walls[k - 1].a2 <= distances[i] && distances[i] <= walls[k - 1].b2) {
                    min_distance = fmin(min_distance, walls[k - 1].a2 - distances[i]);
                }
                if (walls[k - 1].a1 <= distances[j] && distances[j] <= walls[k - 1].b1) {
                    min_distance = fmin(min_distance, distances[j] - walls[k - 1].b1);
                }
                if (walls[k - 1].a2 <= distances[j] && distances[j] <= walls[k - 1].b2) {
                    min_distance = fmin(min_distance, distances[j] - walls[k - 1].b2);
                }
            }
            distances[i] += min_distance;
        }
    }

    // 输出最短距离
    printf("%.2lf\n", distances[n + 1]);
    return 0;
}