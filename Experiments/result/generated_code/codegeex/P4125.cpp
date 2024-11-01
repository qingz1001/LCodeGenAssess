#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 50005

typedef struct Segment {
    int x1, y1, x2, y2;
} Segment;

Segment segments[MAXN];
int n;
bool blocked[MAXN];

// 检查某个线段是否被其他线段阻挡
bool isBlocked(int segmentIndex, int direction) {
    int x1, y1, x2, y2;
    x1 = segments[segmentIndex].x1;
    y1 = segments[segmentIndex].y1;
    x2 = segments[segmentIndex].x2;
    y2 = segments[segmentIndex].y2;

    switch (direction) {
        case 0: // 向左平移
            x2 = x1 - 1;
            break;
        case 1: // 向上平移
            y2 = y1 + 1;
            break;
        case 2: // 向右平移
            x2 = x1 + 1;
            break;
        case 3: // 向下平移
            y2 = y1 - 1;
            break;
    }

    for (int i = 0; i < n; i++) {
        if (i != segmentIndex && !blocked[i]) {
            if (segments[i].x1 <= x2 && x2 <= segments[i].x2 && segments[i].y1 <= y2 && y2 <= segments[i].y2) {
                return true;
            }
            if (segments[i].x1 <= x1 && x1 <= segments[i].x2 && segments[i].y1 <= y1 && y1 <= segments[i].y2) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }

    int illegalMove = -1;
    for (int i = 0; i < n; i++) {
        int p, q;
        scanf("%d %d", &p, &q);
        p--; // 转换为0索引

        if (isBlocked(p, q)) {
            illegalMove = i + 1;
            break;
        } else {
            blocked[p] = true;
            printf("%d %d\n", p + 1, q); // 输出合法移动方案
        }
    }

    printf("%d\n", illegalMove);

    return 0;
}