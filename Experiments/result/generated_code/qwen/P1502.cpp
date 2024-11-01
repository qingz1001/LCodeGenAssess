#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int x, y, l;
} Star;

int compare(const void *a, const void *b) {
    return ((Star *)b)->y - ((Star *)a)->y;
}

long long maxBrightness(int n, int W, int H, Star stars[]) {
    qsort(stars, n, sizeof(Star), compare);
    long long maxSum = 0, currentSum = 0;
    for (int i = 0; i < n; ++i) {
        if (stars[i].y > H) continue;
        if (stars[i].x + W <= 2000000000) {
            currentSum += stars[i].l;
            maxSum = fmax(maxSum, currentSum);
        }
    }
    return maxSum;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, W, H;
        scanf("%d %d %d", &n, &W, &H);
        Star stars[MAXN];
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d", &stars[i].x, &stars[i].y, &stars[i].l);
        }
        printf("%lld\n", maxBrightness(n, W, H, stars));
    }
    return 0;
}