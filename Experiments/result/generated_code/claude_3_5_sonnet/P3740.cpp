#include <stdio.h>
#include <stdlib.h>

#define MAX_M 1000
#define MAX_N 10000000

typedef struct {
    int left;
    int right;
} Poster;

int compare(const void *a, const void *b) {
    return ((Poster *)b)->right - ((Poster *)a)->right;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Poster posters[MAX_M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &posters[i].left, &posters[i].right);
    }

    qsort(posters, M, sizeof(Poster), compare);

    int visible = 0;
    int last_covered = 0;

    for (int i = 0; i < M; i++) {
        if (posters[i].left > last_covered) {
            visible++;
            last_covered = posters[i].right;
        }
    }

    printf("%d\n", visible);

    return 0;
}