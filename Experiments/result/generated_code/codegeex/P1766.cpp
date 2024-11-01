#include <stdio.h>
#include <stdlib.h>

// 定义线段结构体
typedef struct {
    int x1, y1, x2, y2;
} Segment;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Segment *segA = (Segment *)a;
    Segment *segB = (Segment *)b;
    if (segA->y1 == segB->y1) {
        return segA->x1 - segB->x1;
    }
    return segA->y1 - segB->y1;
}

int main() {
    int N, S;
    scanf("%d %d", &N, &S);

    Segment segments[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }

    // 按照y1坐标排序，如果y1相同则按x1排序
    qsort(segments, N, sizeof(Segment), compare);

    int currentX = S;
    int currentY = 0;
    int nextY = 0;
    int nextX = 0;

    while (1) {
        int maxNextY = -1;
        int maxNextX = 0;

        // 找到液滴可以滴到的下一个轨道
        for (int i = 0; i < N; i++) {
            if (segments[i].y1 > currentY) {
                int intersectionX = currentX + (segments[i].y1 - currentY) * (segments[i].x2 - segments[i].x1) / (segments[i].y2 - segments[i].y1);
                if (intersectionX >= segments[i].x1 && intersectionX <= segments[i].x2) {
                    if (segments[i].y1 > maxNextY) {
                        maxNextY = segments[i].y1;
                        maxNextX = intersectionX;
                    }
                }
            }
        }

        if (maxNextY == -1) {
            // 没有找到下一个轨道，液滴垂直滴落
            printf("%d\n", currentX);
            break;
        } else {
            // 更新液滴的位置
            currentY = maxNextY;
            currentX = maxNextX;
        }
    }

    return 0;
}