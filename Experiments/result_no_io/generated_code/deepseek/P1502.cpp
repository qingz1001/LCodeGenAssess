#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000

typedef struct {
    int x, y, l;
} Star;

int compare(const void *a, const void *b) {
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
        Star stars[MAXN];
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &stars[i].x, &stars[i].y, &stars[i].l);
        }

        qsort(stars, n, sizeof(Star), compare);

        int max_brightness = 0;
        for (int i = 0; i < n; i++) {
            int window_brightness = 0;
            for (int j = i; j < n; j++) {
                if (stars[j].x - stars[i].x >= W) break;
                if (stars[j].y < stars[i].y || stars[j].y >= stars[i].y + H) continue;
                window_brightness += stars[j].l;
            }
            max_brightness = max(max_brightness, window_brightness);
        }

        printf("%d\n", max_brightness);
    }
    return 0;
}