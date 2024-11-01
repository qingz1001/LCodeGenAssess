#include <stdio.h>
#include <stdlib.h>

#define MAX_N 201

int main() {
    int m, s, c;
    scanf("%d %d %d", &m, &s, &c);
    int cows[MAX_N];
    for (int i = 0; i < c; i++) {
        scanf("%d", &cows[i]);
    }

    // Sort the cow stalls
    qsort(cows, c, sizeof(int), (int (*)(const void *, const void *))strcmp);

    int min_length = INT_MAX;
    for (int i = 0; i <= c - m; i++) {
        int length = cows[i + m - 1] - cows[i] + 1;
        if (length < min_length) {
            min_length = length;
        }
    }

    printf("%d\n", min_length);
    return 0;
}