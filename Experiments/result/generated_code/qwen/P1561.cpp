#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25000
#define MAX_U_D 50000

int main() {
    int N;
    scanf("%d", &N);

    int up[MAX_N], down[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d", &up[i], &down[i]);
    }

    // Sort the up and down times
    qsort(up, N, sizeof(int), (int (*)(const void *, const void *))strcmp);
    qsort(down, N, sizeof(int), (int (*)(const void *, const void *))strcmp);

    int total_time = 0;
    for (int i = 0; i < N; ++i) {
        total_time += up[i] + down[N - 1 - i];
    }

    printf("%d\n", total_time);

    return 0;
}