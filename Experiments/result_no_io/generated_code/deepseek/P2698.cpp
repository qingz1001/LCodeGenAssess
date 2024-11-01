#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Drop;

int compare_drops(const void *a, const void *b) {
    return ((Drop *)a)->x - ((Drop *)b)->x;
}

int main() {
    int N, D;
    scanf("%d %d", &N, &D);

    Drop drops[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &drops[i].x, &drops[i].y);
    }

    qsort(drops, N, sizeof(Drop), compare_drops);

    int min_width = -1;
    int left = 0, right = 0;

    while (right < N) {
        if (drops[right].y - drops[left].y >= D) {
            int width = drops[right].x - drops[left].x;
            if (min_width == -1 || width < min_width) {
                min_width = width;
            }
            left++;
        } else {
            right++;
        }
    }

    printf("%d\n", min_width);

    return 0;
}