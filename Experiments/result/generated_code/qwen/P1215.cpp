#include <stdio.h>
#include <stdlib.h>

#define MAX_BUCKET_SIZE 20

void pour(int from, int to, int *buckets) {
    if (from == -1 || buckets[from] == 0) return;
    int can_pour = fmin(buckets[from], buckets[to]);
    buckets[from] -= can_pour;
    buckets[to] += can_pour;
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int possible_values[MAX_BUCKET_SIZE + 1] = {0};
    for (int i = 0; i <= c; i++) possible_values[i] = 1;

    int buckets[3] = {0, 0, c};

    while (1) {
        pour(0, 1, buckets);
        pour(0, 2, buckets);
        pour(1, 0, buckets);
        pour(1, 2, buckets);
        pour(2, 0, buckets);
        pour(2, 1, buckets);

        if (buckets[0] == 0 && possible_values[buckets[2]] == 0) break;

        possible_values[buckets[2]] = 1;
    }

    for (int i = 0; i <= c; i++) {
        if (possible_values[i]) printf("%d ", i);
    }
    printf("\n");

    return 0;
}