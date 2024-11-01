#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_COORD 1000000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N;
    scanf("%d", &N);

    int x[MAX_N], y[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &x[i], &y[i]);
    }

    qsort(x, N, sizeof(int), compare);
    qsort(y, N, sizeof(int), compare);

    int mid_x = x[N / 2];
    int mid_y = y[N / 2];

    int count[4] = {0};
    for (int i = 0; i < N; ++i) {
        if (x[i] <= mid_x && y[i] <= mid_y) {
            count[0]++;
        } else if (x[i] > mid_x && y[i] <= mid_y) {
            count[1]++;
        } else if (x[i] <= mid_x && y[i] > mid_y) {
            count[2]++;
        } else {
            count[3]++;
        }
    }

    int M = 0;
    for (int i = 0; i < 4; ++i) {
        if (count[i] > M) {
            M = count[i];
        }
    }

    printf("%d\n", M);

    return 0;
}