#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAX_COORD 1000000000

typedef struct {
    int x, y;
    char orientation;
} Mirror;

int main() {
    int N, Bx, By;
    scanf("%d %d %d", &N, &Bx, &By);

    Mirror mirrors[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %c", &mirrors[i].x, &mirrors[i].y, &mirrors[i].orientation);
    }

    int *x_coords = (int *)calloc(MAX_COORD * 2 + 1, sizeof(int));
    int *y_coords = (int *)calloc(MAX_COORD * 2 + 1, sizeof(int));

    for (int i = 0; i < N; i++) {
        int x = mirrors[i].x;
        int y = mirrors[i].y;
        char orientation = mirrors[i].orientation;

        if (orientation == '\\') {
            x_coords[x + y]++;
            y_coords[x - y]++;
        } else {
            x_coords[x - y]++;
            y_coords[x + y]++;
        }
    }

    int count = 0;
    for (int i = -MAX_COORD; i <= MAX_COORD; i++) {
        if (x_coords[i] == 0 && y_coords[i] == 0) {
            count++;
        }
    }

    printf("%d\n", count);

    free(x_coords);
    free(y_coords);

    return 0;
}