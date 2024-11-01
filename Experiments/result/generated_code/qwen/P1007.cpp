#include <stdio.h>
#include <stdlib.h>

int main() {
    int L, N;
    scanf("%d %d", &L, &N);
    int *positions = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &positions[i]);
    }

    int min_time = 0;
    int max_time = 0;

    for (int i = 0; i < N; i++) {
        if (positions[i] <= (L + 1) / 2) {
            min_time = positions[i];
        } else {
            min_time = L - positions[i] + 1;
        }
        if (positions[i] >= (L + 1) / 2) {
            max_time = L - positions[i] + 1;
        } else {
            max_time = positions[i];
        }
    }

    printf("%d %d\n", min_time, max_time);

    free(positions);
    return 0;
}