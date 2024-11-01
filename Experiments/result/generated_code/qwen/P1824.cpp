#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N, C;
    scanf("%d %d", &N, &C);

    int stalls[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &stalls[i]);
    }

    qsort(stalls, N, sizeof(int), compare);

    int low = 1, high = stalls[N-1] - stalls[0], result = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        int count = 1, last_position = stalls[0];

        for (int i = 1; i < N; i++) {
            if (stalls[i] - last_position >= mid) {
                count++;
                last_position = stalls[i];
            }
        }

        if (count >= C) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", result);

    return 0;
}