#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    int h, w;
} Chocolate;

int compare(const void *a, const void *b) {
    return ((Chocolate *)b)->h * ((Chocolate *)b)->w - ((Chocolate *)a)->h * ((Chocolate *)a)->w;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    Chocolate chocolates[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &chocolates[i].h, &chocolates[i].w);
    }

    qsort(chocolates, N, sizeof(Chocolate), compare);

    int max_side = 0;
    for (int i = 0; i < N && K > 0; i++) {
        int min_dim = chocolates[i].h < chocolates[i].w ? chocolates[i].h : chocolates[i].w;
        while (min_dim > 0 && K >= min_dim * min_dim) {
            K -= min_dim * min_dim;
            max_side = min_dim;
            min_dim--;
        }
    }

    printf("%d\n", max_side);
    return 0;
}