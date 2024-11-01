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
    } else {
        return segA->y1 - segB->y1;
    }
}

int main() {
    int N, S;
    scanf("%d %d", &N, &S);

    Segment segments[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }

    // 按照y1排序，如果y1相同则按照x1排序
    qsort(segments, N, sizeof(Segment), compare);

    int currentX = S;
    int currentY = 0;

    while (1) {
        int nextY = -1;
        int nextSegmentIndex = -1;

        // 找到液滴会滴落的下一个轨道
        for (int i = 0; i < N; i++) {
            if (segments[i].x1 <= currentX && segments[i].x2 >= currentX && segments[i].y1 > currentY) {
                if (nextY == -1 || segments[i].y1 < nextY) {
                    nextY = segments[i].y1;
                    nextSegmentIndex = i;
                }
            }
        }

        if (nextY == -1) {
            // 没有找到下一个轨道，液滴垂直滴落
            printf("%d\n", currentX);
            break;
        } else {
            // 找到下一个轨道，液滴沿着轨道滴落
            currentX = (currentX - segments[nextSegmentIndex].x1) * (segments[nextSegmentIndex].y2 - segments[nextSegmentIndex].y1) / (segments[nextSegmentIndex].x2 - segments[nextSegmentIndex].x1) + segments[nextSegmentIndex].x1;
            currentY = nextY;
        }
    }

    return 0;
}