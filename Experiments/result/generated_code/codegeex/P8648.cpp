#include <stdio.h>
#include <stdlib.h>

// 定义矩形结构体
typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Rectangle *rectA = (Rectangle *)a;
    Rectangle *rectB = (Rectangle *)b;
    if (rectA->x1 != rectB->x1) {
        return rectA->x1 - rectB->x1;
    } else {
        return rectA->y1 - rectB->y1;
    }
}

// 计算两个矩形的重叠面积
int overlapArea(Rectangle rect1, Rectangle rect2) {
    int xOverlap = (rect1.x2 > rect2.x1) ? (rect1.x2 < rect2.x2 ? rect1.x2 : rect2.x2) - (rect1.x1 > rect2.x1 ? rect1.x1 : rect2.x1) : 0;
    int yOverlap = (rect1.y2 > rect2.y1) ? (rect1.y2 < rect2.y2 ? rect1.y2 : rect2.y2) - (rect1.y1 > rect2.y1 ? rect1.y1 : rect2.y1) : 0;
    return xOverlap * yOverlap;
}

int main() {
    int n;
    scanf("%d", &n);
    Rectangle rectangles[n];

    // 读取矩形数据
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
    }

    // 对矩形按x1, y1排序
    qsort(rectangles, n, sizeof(Rectangle), compare);

    int totalArea = 0;
    int currentX = rectangles[0].x1;
    int currentY = rectangles[0].y1;
    int currentX2 = rectangles[0].x2;
    int currentY2 = rectangles[0].y2;

    for (int i = 1; i < n; i++) {
        Rectangle currentRect = rectangles[i];
        int overlap = overlapArea((Rectangle){currentX, currentY, currentX2, currentY2}, currentRect);

        if (overlap > 0) {
            // 计算当前重叠区域面积并加上
            totalArea += (currentX2 - currentX) * (currentY2 - currentY) - overlap;
        }

        // 更新当前矩形的最右下角
        currentX = currentRect.x1 < currentX ? currentRect.x1 : currentX;
        currentY = currentRect.y1 < currentY ? currentRect.y1 : currentY;
        currentX2 = currentRect.x2 > currentX2 ? currentRect.x2 : currentX2;
        currentY2 = currentRect.y2 > currentY2 ? currentRect.y2 : currentY2;
    }

    // 添加最后一个矩形的面积
    totalArea += (currentX2 - currentX) * (currentY2 - currentY);

    printf("%d\n", totalArea);
    return 0;
}