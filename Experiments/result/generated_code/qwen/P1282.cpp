#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *top = (int *)malloc(n * sizeof(int));
    int *bottom = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &top[i], &bottom[i]);
    }

    int min_rotations = INT_MAX;

    for (int i = 0; i < n; i++) {
        int rotations = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                rotations += abs(top[j] - bottom[j]);
            } else {
                rotations += abs(top[j] - top[j]) + abs(bottom[j] - bottom[j]);
            }
        }
        if (rotations < min_rotations) {
            min_rotations = rotations;
        }
    }

    printf("%d\n", min_rotations);

    free(top);
    free(bottom);

    return 0;
}