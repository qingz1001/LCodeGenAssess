#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y, l;
} Star;

int compareStars(const void *a, const void *b) {
    return ((Star *)a)->x - ((Star *)b)->x;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, W, H;
        scanf("%d %d %d", &n, &W, &H);
        Star stars[n];
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &stars[i].x, &stars[i].y, &stars[i].l);
        }

        qsort(stars, n, sizeof(Star), compareStars);

        int maxBrightness = 0;
        for (int i = 0; i < n; i++) {
            int currentBrightness = 0;
            for (int j = i; j < n; j++) {
                if (stars[j].x < stars[i].x + W) {
                    currentBrightness += stars[j].l;
                } else {
                    break;
                }
            }
            maxBrightness = max(maxBrightness, currentBrightness);
        }

        printf("%d\n", maxBrightness);
    }
    return 0;
}