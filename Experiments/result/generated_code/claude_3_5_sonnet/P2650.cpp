#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    int start;
    int end;
} Danmaku;

int cmp(const void *a, const void *b) {
    return ((Danmaku*)a)->start - ((Danmaku*)b)->start;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Danmaku danmaku[MAX_N];
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        danmaku[i].start = a + 1;
        danmaku[i].end = a + b;
    }

    qsort(danmaku, n, sizeof(Danmaku), cmp);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int end = x + y;
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (danmaku[j].start > end) break;
            if (danmaku[j].end >= x + 1 && danmaku[j].start <= end) {
                count++;
            }
        }
        printf("%d\n", count);
    }

    return 0;
}