#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int *heights = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    int left = 0, right = 400000;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        long long total = 0;
        for (int i = 0; i < N; i++) {
            if (heights[i] > mid) {
                total += heights[i] - mid;
            }
        }
        if (total >= M) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", left);

    free(heights);
    return 0;
}