#include <stdio.h>
#include <stdlib.h>

#define MAXN 50
#define MAXS 30

typedef struct {
    int id;
    int size;
    int x;
} Square;

int compare(const void *a, const void *b) {
    return ((Square *)a)->size - ((Square *)b)->size;
}

int main() {
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        Square squares[MAXN];
        for (int i = 0; i < n; i++) {
            squares[i].id = i + 1;
            scanf("%d", &squares[i].size);
        }

        // Sort squares by size in ascending order
        qsort(squares, n, sizeof(Square), compare);

        // Calculate x-coordinates
        squares[0].x = 0;
        for (int i = 1; i < n; i++) {
            squares[i].x = squares[i-1].x + squares[i-1].size;
        }

        // Output visible squares
        int visible[MAXN];
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (i == 0 || squares[i].x < squares[i-1].x + squares[i-1].size) {
                visible[count++] = squares[i].id;
            }
        }

        // Print visible squares
        for (int i = 0; i < count; i++) {
            if (i > 0) printf(" ");
            printf("%d", visible[i]);
        }
        printf("\n");
    }

    return 0;
}