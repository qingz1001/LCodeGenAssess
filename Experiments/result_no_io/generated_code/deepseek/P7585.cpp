#include <stdio.h>
#include <stdlib.h>

#define MAX_M 300000

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int *balls = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) {
        scanf("%d", &balls[i]);
    }

    qsort(balls, M, sizeof(int), compare);

    int left = 1, right = balls[0];
    while (left < right) {
        int mid = (left + right) / 2;
        int count = 0;
        for (int i = 0; i < M; i++) {
            count += (balls[i] + mid - 1) / mid;
        }
        if (count <= N) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", left);

    free(balls);
    return 0;
}