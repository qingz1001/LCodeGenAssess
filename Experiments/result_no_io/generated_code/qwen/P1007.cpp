#include <stdio.h>
#include <stdlib.h>

int main() {
    int L, N;
    scanf("%d %d", &L, &N);
    int *positions = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &positions[i]);
    }

    // Calculate the minimum time to evacuate
    int min_time = 0;
    for (int i = 0; i < N; i++) {
        if (positions[i] > (L + 1) / 2) {
            min_time = positions[i];
        } else {
            min_time = L - positions[i] + 1;
        }
    }

    // Calculate the maximum time to evacuate
    int max_time = 0;
    for (int i = 0; i < N; i++) {
        if (positions[i] <= (L + 1) / 2) {
            max_time = positions[i];
        } else {
            max_time = L - positions[i] + 1;
        }
    }

    printf("%d %d\n", min_time, max_time);

    free(positions);
    return 0;
}