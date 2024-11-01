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
    scanf("%d%d", &N, &D);
    
    Raindrop drops[N];
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &drops[i].x, &drops[i].y);
    }

    qsort(drops, N, sizeof(Raindrop), compare);

    int min_width = -1;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (drops[j].y - drops[i].y >= D) {
                int width = drops[j].x - drops[i].x;
                if (min_width == -1 || width < min_width) {
                    min_width = width;
                }
                break;
            }
        }
    }

    printf("%d\n", min_width);
    return 0;
}