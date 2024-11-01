#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    double x; // 正方形与x轴交点的x坐标
    double length; // 正方形的边长
} Square;

int compare(const void *a, const void *b) {
    Square *squareA = (Square *)a;
    Square *squareB = (Square *)b;
    if (squareA->x != squareB->x) {
        return squareA->x > squareB->x ? 1 : -1;
    } else {
        return squareA->length < squareB->length ? 1 : -1;
    }
}

int main() {
    int n;
    while (scanf("%d", &n) && n != 0) {
        Square squares[50];
        for (int i = 0; i < n; i++) {
            squares[i].index = i + 1;
            scanf("%lf", &squares[i].length);
            squares[i].x = squares[i].length * 0.707106781186548; // 正方形边长的一半乘以√2
        }

        qsort(squares, n, sizeof(Square), compare);

        int max_x = 0;
        for (int i = 0; i < n; i++) {
            if (squares[i].x + squares[i].length / 2.0 > max_x) {
                printf("%d ", squares[i].index);
                max_x = squares[i].x + squares[i].length / 2.0;
            }
        }
        printf("\n");
    }
    return 0;
}