#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义一个点结构体
typedef struct {
    int x, y;
} Point;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Point *pointA = (Point *)a;
    Point *pointB = (Point *)b;
    if (pointA->x != pointB->x) {
        return pointA->x - pointB->x;
    } else {
        return pointA->y - pointB->y;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[N];

    // 读取点的坐标
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    // 对点进行排序
    qsort(points, N, sizeof(Point), compare);

    // 计算每个点作为起始点时的最短距离和最长距离
    int minDifference = INT_MAX;
    for (int i = 0; i < N; i++) {
        int maxDistance = 0;
        int minDistance = INT_MAX;

        // 计算与当前点i的距离
        for (int j = 0; j < N; j++) {
            if (i != j) {
                int distance = (points[i].x - points[j].x) * (points[i].x - points[j].x) +
                               (points[i].y - points[j].y) * (points[i].y - points[j].y);
                if (distance > maxDistance) {
                    maxDistance = distance;
                }
                if (distance < minDistance) {
                    minDistance = distance;
                }
            }
        }

        // 计算距离差
        int difference = maxDistance - minDistance;
        if (difference < minDifference) {
            minDifference = difference;
        }
    }

    // 输出最小距离差
    printf("%d\n", minDifference);
    return 0;
}