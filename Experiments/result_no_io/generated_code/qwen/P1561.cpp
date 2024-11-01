#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25000
#define MAX_TIME 50000

int main() {
    int N;
    scanf("%d", &N);

    int *up = malloc(N * sizeof(int));
    int *down = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &up[i], &down[i]);
    }

    // Sort up times in ascending order
    qsort(up, N, sizeof(int), compare);
    // Sort down times in descending order
    qsort(down, N, sizeof(int), compare_desc);

    int totalTime = 0;
    int j = 0;

    for (int i = 0; i < N; i++) {
        totalTime += up[i];
        while (j < N && down[j] >= up[i]) {
            j++;
        }
        if (j < N) {
            totalTime += down[j++];
        }
    }

    printf("%d\n", totalTime);

    free(up);
    free(down);

    return 0;
}

// Comparison function for qsort in ascending order
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Comparison function for qsort in descending order
int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}