#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_D 1000000

typedef struct {
    int x;
    int y;
} Drop;

int compare(const void *a, const void *b) {
    return ((Drop *)a)->y - ((Drop *)b)->y;
}

int main() {
    int N, D;
    scanf("%d %d", &N, &D);

    Drop drops[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &drops[i].x, &drops[i].y);
    }

    qsort(drops, N, sizeof(Drop), compare);

    int min_width = -1;
    for (int i = 0; i <= N - 2; i++) {
        if (drops[i + 1].y - drops[i].y >= D) {
            min_width = drops[i + 1].x - drops[i].x;
            break;
        }
    }

    printf("%d\n", min_width);

    return 0;
}