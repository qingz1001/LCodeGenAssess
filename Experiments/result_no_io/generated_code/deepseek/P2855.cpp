#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int can_remove_rocks(int *rocks, int N, int M, int L, int min_dist) {
    int removed = 0;
    int last_rock = 0;
    for (int i = 0; i < N; i++) {
        if (rocks[i] - last_rock < min_dist) {
            removed++;
        } else {
            last_rock = rocks[i];
        }
    }
    if (L - last_rock < min_dist) {
        removed++;
    }
    return removed <= M;
}

int main() {
    int L, N, M;
    scanf("%d %d %d", &L, &N, &M);

    int *rocks = (int *)malloc((N + 2) * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &rocks[i]);
    }
    rocks[N] = 0; // Starting rock
    rocks[N + 1] = L; // Ending rock

    qsort(rocks, N + 2, sizeof(int), compare);

    int left = 0, right = L;
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (can_remove_rocks(rocks, N + 2, M, L, mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);

    free(rocks);
    return 0;
}