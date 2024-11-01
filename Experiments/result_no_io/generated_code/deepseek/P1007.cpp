#include <stdio.h>
#include <stdlib.h>

int main() {
    int L, N;
    scanf("%d", &L);
    scanf("%d", &N);

    int *positions = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &positions[i]);
    }

    int min_time = 0, max_time = 0;

    // 计算最小时间
    for (int i = 0; i < N; i++) {
        int time_to_edge = positions[i] - 1;
        if (L - positions[i] + 1 < time_to_edge) {
            time_to_edge = L - positions[i] + 1;
        }
        if (time_to_edge > min_time) {
            min_time = time_to_edge;
        }
    }

    // 计算最大时间
    for (int i = 0; i < N; i++) {
        int time_to_edge = positions[i] - 1;
        if (L - positions[i] + 1 > time_to_edge) {
            time_to_edge = L - positions[i] + 1;
        }
        if (time_to_edge > max_time) {
            max_time = time_to_edge;
        }
    }

    printf("%d %d\n", min_time, max_time);

    free(positions);
    return 0;
}