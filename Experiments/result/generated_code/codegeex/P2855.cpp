#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50001

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int L, N, M;
    scanf("%d%d%d", &L, &N, &M);

    int rocks[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &rocks[i]);
    }

    qsort(rocks, N, sizeof(int), cmp);

    // Add the start and end points
    rocks[N] = L;
    N++;

    int left = 0, right = L, result = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        int count = 0;

        for (int i = 1; i < N; i++) {
            if (rocks[i] - rocks[i - 1] < mid) {
                count++;
            }
        }

        if (count <= M) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}