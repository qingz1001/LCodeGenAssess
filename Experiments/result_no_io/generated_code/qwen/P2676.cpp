#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int minCowStack(int heights[], int n, int bookshelfHeight) {
    qsort(heights, n, sizeof(int), compare);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += heights[i];
        if (sum >= bookshelfHeight) {
            return i + 1;
        }
    }

    return n;
}

int main() {
    int n, bookshelfHeight;
    scanf("%d %d", &n, &bookshelfHeight);

    int *heights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int result = minCowStack(heights, n, bookshelfHeight);
    printf("%d\n", result);

    free(heights);
    return 0;
}