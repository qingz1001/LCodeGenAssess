#include <stdio.h>

// 定义矩形结构体
typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    Rectangle *rectA = (Rectangle *)a;
    Rectangle *rectB = (Rectangle *)b;
    if (rectA->x1 != rectB->x1)
        return rectA->x1 - rectB->x1;
    else
        return rectA->y1 - rectB->y1;
}

int main() {
    int n;
    scanf("%d", &n);
    Rectangle rects[n];
    
    // 读取所有矩形的坐标
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &rects[i].x1, &rects[i].y1, &rects[i].x2, &rects[i].y2);
    }
    
    // 按照左下角坐标排序
    qsort(rects, n, sizeof(Rectangle), cmp);
    
    int totalArea = 0;
    int x = 0, y = 0;
    
    // 遍历所有矩形，计算覆盖面积
    for (int i = 0; i < n; i++) {
        int x1 = rects[i].x1;
        int y1 = rects[i].y1;
        int x2 = rects[i].x2;
        int y2 = rects[i].y2;
        
        // 确保x1 < x2, y1 < y2
        if (x1 > x2) {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }
        if (y1 > y2) {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }
        
        // 计算覆盖的面积
        int width = x2 - x1;
        int height = y2 - y1;
        int area = width * height;
        
        // 累加面积
        totalArea += area;
    }
    
    // 输出总面积
    printf("%d\n", totalArea);
    
    return 0;
}