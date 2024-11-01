#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 50

typedef struct {
    int index;
    int size;
    double x;
} Square;

int compare(const void *a, const void *b) {
    Square *sa = (Square *)a;
    Square *sb = (Square *)b;
    return sa->x - sb->x > 0 ? 1 : -1;
}

int main() {
    int n, i, j;
    Square squares[MAX_N];

    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        for (i = 0; i < n; i++) {
            scanf("%d", &squares[i].size);
            squares[i].index = i + 1;
        }

        squares[0].x = squares[0].size * sqrt(2) / 2;

        for (i = 1; i < n; i++) {
            double min_x = squares[i].size * sqrt(2) / 2;
            for (j = 0; j < i; j++) {
                double dx = squares[j].x + (squares[i].size + squares[j].size) * sqrt(2) / 2;
                if (dx > min_x) min_x = dx;
            }
            squares[i].x = min_x;
        }

        qsort(squares, n, sizeof(Square), compare);

        double max_right = 0;
        for (i = 0; i < n; i++) {
            if (squares[i].x + squares[i].size * sqrt(2) / 2 > max_right) {
                printf("%d ", squares[i].index);
                max_right = squares[i].x + squares[i].size * sqrt(2) / 2;
            }
        }
        printf("\n");
    }

    return 0;
}