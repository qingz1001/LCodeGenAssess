#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minUnsortedness(int heights[], int widths[], int n, int k) {
    int pairs[n];
    for (int i = 0; i < n; i++) {
        pairs[i] = abs(heights[i] - widths[i]);
    }
    qsort(pairs, n, sizeof(int), compare);
    int sum = 0;
    for (int i = 0; i < n - k; i++) {
        sum += pairs[i];
    }
    return sum;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int heights[n], widths[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &heights[i], &widths[i]);
    }
    printf("%d\n", minUnsortedness(heights, widths, n, k));
    return 0;
}