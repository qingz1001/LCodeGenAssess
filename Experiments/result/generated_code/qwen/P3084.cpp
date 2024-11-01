#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200001
#define MAX_M 100001

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int a[MAX_M], b[MAX_M];
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &a[i], &b[i]);
    }

    // Initialize an array to keep track of the minimum and maximum positions where spotted cows can be
    int min_pos[MAX_N + 1];
    int max_pos[MAX_N + 1];
    for (int i = 0; i <= N; ++i) {
        min_pos[i] = MAX_N;
        max_pos[i] = 0;
    }

    // Update the minimum and maximum positions based on the photos
    for (int i = 0; i < M; ++i) {
        min_pos[a[i]] = a[i];
        max_pos[b[i]] = b[i];
    }

    // Calculate the range where spotted cows can be
    int start = MAX_N;
    int end = 0;
    for (int i = 1; i <= N; ++i) {
        if (min_pos[i] != MAX_N && max_pos[i] != 0) {
            start = start < min_pos[i] ? start : min_pos[i];
            end = end > max_pos[i] ? end : max_pos[i];
        }
    }

    // Check if there is a valid range for spotted cows
    if (start == MAX_N || end == 0 || start > end) {
        printf("-1\n");
    } else {
        printf("%d\n", end - start + 1);
    }

    return 0;
}