#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minCows(int heights[], int n, int B) {
    qsort(heights, n, sizeof(int), compare);

    int left = 0, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        int sum = 0, count = 1;

        for (int i = mid; i >= 0 && sum <= B; i--) {
            if (sum + heights[i] > B) break;
            sum += heights[i];
            count++;
        }

        if (count == mid + 1) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);
    int heights[N];

    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    printf("%d\n", minCows(heights, N, B));

    return 0;
}