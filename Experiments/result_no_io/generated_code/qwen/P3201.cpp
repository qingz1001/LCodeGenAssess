#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int *colors = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &colors[i]);
    }

    int *last_color_pos = (int *)calloc(1000001, sizeof(int));
    int *color_count = (int *)calloc(1000001, sizeof(int));
    int segment_count = 0;

    for (int i = 0; i < n; i++) {
        if (color_count[colors[i]] == 0) {
            segment_count++;
        }
        color_count[colors[i]]++;
    }

    for (int i = 0; i <= 1000000; i++) {
        last_color_pos[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (last_color_pos[colors[i]] != -1) {
            segment_count--;
        }
        last_color_pos[colors[i]] = i;
        color_count[colors[i]]++;
    }

    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            if (color_count[x] > 0) {
                segment_count -= color_count[x];
                color_count[x] = 0;
            }
            if (color_count[y] == 0) {
                segment_count++;
            }
            color_count[y]++;
        } else if (op == 2) {
            printf("%d\n", segment_count);
        }
    }

    free(colors);
    free(last_color_pos);
    free(color_count);

    return 0;
}