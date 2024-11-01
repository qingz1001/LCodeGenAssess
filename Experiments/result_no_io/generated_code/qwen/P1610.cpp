#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, dist;
    scanf("%d %d", &n, &dist);
    int p[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    qsort(p, n, sizeof(int), compare);

    int max_deletable = 0;
    int start = 0;

    for (int end = 1; end < n; end++) {
        if (p[end] - p[start] > dist) {
            max_deletable += end - start - 1;
            start = end;
        }
    }

    max_deletable += n - start - 2;

    printf("%d\n", max_deletable);

    return 0;
}