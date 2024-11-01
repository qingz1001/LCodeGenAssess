#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Raindrop;

int compare(const void *a, const void *b) {
    Raindrop *dropA = (Raindrop *)a;
    Raindrop *dropB = (Raindrop *)b;
    return dropA->x - dropB->x;
}

int main() {
    int N, D;
    scanf("%d %d", &N, &D);
    Raindrop drops[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &drops[i].x, &drops[i].y);
    }

    qsort(drops, N, sizeof(Raindrop), compare);

    int left = 0, right = 0;
    int min_width = -1;

    while (right < N) {
        while (right < N && drops[right].y - drops[left].y < D) {
            right++;
        }
        if (right < N) {
            int width = drops[right].x - drops[left].x;
            if (min_width == -1 || width < min_width) {
                min_width = width;
            }
        }
        left++;
    }

    printf("%d\n", min_width);
    return 0;
}