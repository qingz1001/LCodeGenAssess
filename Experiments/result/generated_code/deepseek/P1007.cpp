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

    for (int i = 0; i < N; i++) {
        int pos = positions[i];
        int time_to_left = pos;
        int time_to_right = L + 1 - pos;

        if (time_to_left > min_time) {
            min_time = time_to_left;
        }
        if (time_to_right > min_time) {
            min_time = time_to_right;
        }

        if (time_to_left > max_time) {
            max_time = time_to_left;
        }
        if (time_to_right > max_time) {
            max_time = time_to_right;
        }
    }

    printf("%d %d\n", min_time, max_time);

    free(positions);
    return 0;
}