#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXW 1000005
#define MAXH 1000005

typedef struct {
    int x, y, l;
} Star;

int compare(const void *a, const void *b) {
    return ((Star *)b)->y - ((Star *)a)->y;
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
            if (stars[i].y <= H) {
                max_brightness += stars[i].l;
            }
        }

        printf("%d\n", max_brightness);
    }
    return 0;
}