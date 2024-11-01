#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, x, y;
    int y_coords[MAX_N];
    long long total_length = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        y_coords[i] = y;
    }

    qsort(y_coords, n, sizeof(int), compare);

    int median_y = y_coords[n / 2];

    for (int i = 0; i < n; i++) {
        total_length += abs(y_coords[i] - median_y);
    }

    printf("%lld\n", total_length);

    return 0;
}