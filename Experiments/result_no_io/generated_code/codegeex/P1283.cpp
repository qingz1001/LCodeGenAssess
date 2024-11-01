#include <stdio.h>
#include <stdlib.h>

#define MAX_RECTANGLES 16
#define MAX_COLOR 20
#define MAX_COORDINATE 99

int rectangles[MAX_RECTANGLES][5]; // 存储矩形的坐标和颜色
int numRectangles; // 矩形的数量
int colorCount[MAX_COLOR + 1]; // 每种颜色的矩形数量
int minBrushes = INT_MAX; // 最少拿起刷子的次数

void dfs(int currentColor, int currentBrushes, int paintedRectangles) {
    if (paintedRectangles == numRectangles) {
        if (currentColor == 0) {
            minBrushes = currentBrushes;
        }
        return;
    }

    for (int i = 0; i < numRectangles; i++) {
        if ((rectangles[i][4] == currentColor || currentColor == 0) && (paintedRectangles & (1 << i)) == 0) {
            int canPaint = 1;
            for (int j = 0; j < i; j++) {
                if ((paintedRectangles & (1 << j)) == 0) {
                    int x1 = rectangles[i][1], y1 = rectangles[i][0], x2 = rectangles[i][3], y2 = rectangles[i][2];
                    int x3 = rectangles[j][1], y3 = rectangles[j][0], x4 = rectangles[j][3], y4 = rectangles[j][2];
                    if (x1 <= x4 && x2 >= x3 && y1 < y4 && y2 > y3) {
                        canPaint = 0;
                        break;
                    }
                }
            }
            if (canPaint) {
                dfs(rectangles[i][4], currentBrushes + (currentColor == 0 ? 1 : 0), paintedRectangles | (1 << i));
            }
        }
    }
}

int main() {
    scanf("%d", &numRectangles);
    for (int i = 0; i < numRectangles; i++) {
        scanf("%d %d %d %d %d", &rectangles[i][0], &rectangles[i][1], &rectangles[i][2], &rectangles[i][3], &rectangles[i][4]);
        colorCount[rectangles[i][4]]++;
    }

    dfs(0, 0, 0);

    printf("%d\n", minBrushes);
    return 0;
}