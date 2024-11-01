#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);

    int *c = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }

    qsort(c, N, sizeof(int), compare);

    int h = 0;
    while (h < N && c[h] + L >= h + 1) {
        h++;
    }

    printf("%d\n", h);

    free(c);
    return 0;
}