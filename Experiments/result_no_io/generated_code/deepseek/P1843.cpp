#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    int *w = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    qsort(w, n, sizeof(int), compare);

    int time = 0;
    while (w[0] > 0) {
        w[0] -= (a + b);
        qsort(w, n, sizeof(int), compare);
        time++;
    }

    free(w);
    printf("%d\n", time);
    return 0;
}