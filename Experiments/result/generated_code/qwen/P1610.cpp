#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int main() {
    int n, dist;
    scanf("%d %d", &n, &dist);
    int p[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    // Sort the positions of the lights
    qsort(p, n, sizeof(int), (int (*)(const void *, const void *))strcmp);

    int max_deletable = 0;
    int start = 0;

    for (int end = 1; end < n; end++) {
        while (p[end] - p[start] > dist) {
            start++;
        }
        max_deletable = fmax(max_deletable, end - start - 1);
    }

    printf("%d\n", max_deletable);

    return 0;
}