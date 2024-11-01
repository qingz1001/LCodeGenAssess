#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int *x = (int *)a;
    int *y = (int *)b;
    if (x[0] != y[0]) return x[0] - y[0];
    else return x[1] - y[1];
}

int main() {
    int n;
    scanf("%d", &n);
    int sticks[2 * n][2];
    for (int i = 0; i < 2 * n; i += 2) {
        scanf("%d %d", &sticks[i][0], &sticks[i + 1]);
    }
    qsort(sticks, 2 * n, sizeof(int) * 2, compare);

    int prepare_time = 1;
    int last_length = sticks[0][0];
    int last_width = sticks[0][1];

    for (int i = 1; i < 2 * n; i += 2) {
        if (sticks[i][0] >= last_length && sticks[i + 1][0] >= last_width) {
            // No additional preparation time needed
        } else {
            prepare_time++;
        }
        last_length = sticks[i][0];
        last_width = sticks[i + 1][0];
    }

    printf("%d\n", prepare_time);
    return 0;
}