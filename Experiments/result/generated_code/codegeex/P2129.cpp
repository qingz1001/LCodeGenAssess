#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Point *armies = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &armies[i].x, &armies[i].y);
    }

    char command;
    int p, q;
    for (int i = 0; i < m; i++) {
        scanf(" %c", &command);
        if (command == 'm') {
            scanf("%d %d", &p, &q);
            for (int j = 0; j < n; j++) {
                armies[j].x += p;
                armies[j].y += q;
            }
        } else if (command == 'x') {
            for (int j = 0; j < n; j++) {
                armies[j].x = -armies[j].x;
            }
        } else if (command == 'y') {
            for (int j = 0; j < n; j++) {
                armies[j].y = -armies[j].y;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", armies[i].x, armies[i].y);
    }

    free(armies);
    return 0;
}