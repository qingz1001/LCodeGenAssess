#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, k;
int h[MAXN], w[MAXN];

int cmp(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &h[i], &w[i]);
    }

    qsort(h, n, sizeof(int), cmp);
    qsort(w, n, sizeof(int), cmp);

    int ans = 0;
    for (int i = 0; i < n && k > 0; i++) {
        int min_side = h[i] < w[i] ? h[i] : w[i];
        while (min_side > 0 && k >= min_side * min_side) {
            k -= min_side * min_side;
            ans = min_side;
            min_side--;
        }
    }

    printf("%d\n", ans);
    return 0;
}