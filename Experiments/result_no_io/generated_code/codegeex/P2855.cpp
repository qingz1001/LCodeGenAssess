#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int L, N, M;
    scanf("%d%d%d", &L, &N, &M);

    int rocks[N+1];
    for (int i = 0; i < N; i++) {
        scanf("%d", &rocks[i]);
    }
    rocks[N] = L;

    qsort(rocks, N+1, sizeof(int), compare);

    int left = 1, right = L, result = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int count = 0;
        for (int i = 0; i < N; i++) {
            if (rocks[i+1] - rocks[i] < mid) {
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