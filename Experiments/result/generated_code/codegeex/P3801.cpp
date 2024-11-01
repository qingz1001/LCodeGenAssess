#include <stdio.h>
#include <stdlib.h>

int n, m, q;
int *x_count, *y_count;

void add_red_fog(int x, int y) {
    x_count[x]++;
    y_count[y]++;
}

int query_red_fog(int x1, int y1, int x2, int y2) {
    int x_red = 0, y_red = 0;
    for (int i = x1; i <= x2; i++) {
        x_red += (x_count[i] > 0) ? 1 : 0;
    }
    for (int i = y1; i <= y2; i++) {
        y_red += (y_count[i] > 0) ? 1 : 0;
    }
    return x_red * (y2 - y1 + 1) + y_red * (x2 - x1 + 1) - (x_red + y_red);
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    x_count = (int *)calloc(n + 1, sizeof(int));
    y_count = (int *)calloc(m + 1, sizeof(int));

    for (int i = 0; i < q; i++) {
        int op, x, y, x1, y1, x2, y2;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x, &y);
            add_red_fog(x, y);
        } else if (op == 2) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            printf("%d\n", query_red_fog(x1, y1, x2, y2));
        }
    }

    free(x_count);
    free(y_count);
    return 0;
}