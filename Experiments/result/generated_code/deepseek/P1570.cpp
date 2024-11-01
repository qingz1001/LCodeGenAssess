#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 200

typedef struct {
    int v;
    int c;
} Spice;

int compare(const void *a, const void *b) {
    Spice *spiceA = (Spice *)a;
    Spice *spiceB = (Spice *)b;
    double ratioA = (double)spiceA->v / spiceA->c;
    double ratioB = (double)spiceB->v / spiceB->c;
    if (ratioA > ratioB) return -1;
    if (ratioA < ratioB) return 1;
    return 0;
}

int main() {
    int n, m;
    Spice spices[MAXN];

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &spices[i].v);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &spices[i].c);
    }

    qsort(spices, n, sizeof(Spice), compare);

    double max_ratio = 0.0;
    for (int i = 0; i < m; i++) {
        max_ratio += spices[i].v;
    }
    for (int i = 0; i < m; i++) {
        max_ratio /= spices[i].c;
    }

    printf("%.3f\n", max_ratio);

    return 0;
}