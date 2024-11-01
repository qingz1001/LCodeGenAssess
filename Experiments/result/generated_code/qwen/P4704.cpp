#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

int main() {
    int n;
    scanf("%d", &n);
    int ropes[MAXN][2];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &ropes[i][0], &ropes[i][1]);
    }

    // Sort the ropes based on their starting points
    qsort(ropes, n, sizeof(ropes[0]), (int (*)(const void *, const void *))compare);

    int cuts = 0;
    int last_cut = 0;

    for (int i = 0; i < n; ++i) {
        if (ropes[i][0] > last_cut) {
            ++cuts;
            last_cut = ropes[i][1];
        }
    }

    printf("%d\n", cuts);

    return 0;
}

// Comparator function to sort ropes by their starting points
int compare(const void *a, const void *b) {
    return ((int *)a)[0] - ((int *)b)[0];
}