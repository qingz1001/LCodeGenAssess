#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 50

typedef struct {
    int id;
    int size;
    double x;
} Square;

int compare(const void *a, const void *b) {
    Square *sa = (Square *)a;
    Square *sb = (Square *)b;
    return sa->x - sb->x > 0 ? 1 : -1;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        Square squares[MAX_N];
        for (int i = 0; i < n; i++) {
            scanf("%d", &squares[i].size);
            squares[i].id = i + 1;
        }

        squares[0].x = squares[0].size * sqrt(2) / 2;
        for (int i = 1; i < n; i++) {
            double x = squares[i].size * sqrt(2) / 2;
            for (int j = 0; j < i; j++) {
                double dx = squares[j].x + squares[j].size * sqrt(2) / 2;
                double dy = squares[j].size * sqrt(2) / 2 - squares[i].size * sqrt(2) / 2;
                if (dy > 0) {
                    double tx = dx + dy;
                    if (tx > x) x = tx;
                }
            }
            squares[i].x = x;
        }

        qsort(squares, n, sizeof(Square), compare);

        double max_right = 0;
        for (int i = 0; i < n; i++) {
            if (squares[i].x + squares[i].size * sqrt(2) / 2 > max_right) {
                if (i > 0) printf(" ");
                printf("%d", squares[i].id);
                max_right = squares[i].x + squares[i].size * sqrt(2) / 2;
            }
        }
        printf("\n");
    }
    return 0;
}