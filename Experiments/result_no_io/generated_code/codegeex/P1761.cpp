#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int side;
    double intersection;
} Square;

int compare(const void *a, const void *b) {
    Square *squareA = (Square *)a;
    Square *squareB = (Square *)b;
    if (squareA->intersection < squareB->intersection) {
        return -1;
    } else if (squareA->intersection > squareB->intersection) {
        return 1;
    } else {
        return squareA->side - squareB->side;
    }
}

int main() {
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        
        Square squares[50];
        for (int i = 0; i < n; i++) {
            squares[i].index = i + 1;
            scanf("%d", &squares[i].side);
            squares[i].intersection = (double)squares[i].side / sqrt(2);
        }
        
        qsort(squares, n, sizeof(Square), compare);
        
        double max_intersection = 0;
        for (int i = 0; i < n; i++) {
            if (squares[i].intersection > max_intersection) {
                printf("%d ", squares[i].index);
                max_intersection = squares[i].intersection;
            }
        }
        printf("\n");
    }
    return 0;
}