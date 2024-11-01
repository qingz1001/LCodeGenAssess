#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10

typedef struct {
    int h;
    int r1;
    int r2;
} Bowl;

int compare(const void *a, const void *b) {
    Bowl *bowlA = (Bowl *)a;
    Bowl *bowlB = (Bowl *)b;
    if (bowlA->r2 == bowlB->r2) return bowlB->h - bowlA->h;
    return bowlB->r2 - bowlA->r2;
}

int main() {
    int n;
    scanf("%d", &n);
    Bowl bowls[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }

    qsort(bowls, n, sizeof(Bowl), compare);

    int minHeight = 0;
    for (int i = 0; i < n; i++) {
        minHeight += bowls[i].h;
    }

    printf("%d\n", minHeight);
    return 0;
}