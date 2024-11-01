#include <stdio.h>
#include <math.h>

// 计算两个点之间的曼哈顿距离
int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int main() {
    int n;
    scanf("%d", &n);
    
    // 读取所有点的坐标
    int x[n], y[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    
    // 初始化最早时刻为无穷大
    int earliest_time = INT_MAX;
    
    // 计算每对点之间的曼哈顿距离，并更新最早时刻
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = manhattan_distance(x[i], y[i], x[j], y[j]);
            earliest_time = fmin(earliest_time, dist);
        }
    }
    
    // 输出最早的时刻
    printf("%d\n", earliest_time);
    
    return 0;
}