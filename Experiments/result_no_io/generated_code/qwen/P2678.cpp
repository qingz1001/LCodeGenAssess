#include <stdio.h>
#include <stdlib.h>

int main() {
    int L, N, M;
    scanf("%d %d %d", &L, &N, &M);

    int *stones = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &stones[i]);
    }

    // Sort the stones array
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (stones[i] > stones[j]) {
                int temp = stones[i];
                stones[i] = stones[j];
                stones[j] = temp;
            }
        }
    }

    int max_jump = 0;
    int left = 0, right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int jumps = 0;
        int last_jump = 0;

        for (int i = 0; i <= mid; i++) {
            jumps += (stones[i] - last_jump) / 2;
            last_jump = stones[i];
        }

        for (int i = mid + 1; i < N; i++) {
            jumps += (stones[i] - last_jump) / 2;
            last_jump = stones[i];
        }

        if (jumps <= M) {
            max_jump = stones[mid];
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", max_jump);

    free(stones);
    return 0;
}