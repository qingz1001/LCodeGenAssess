#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Danmaku;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Danmaku *danmakus = (Danmaku *)malloc(n * sizeof(Danmaku));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &danmakus[i].start, &danmakus[i].end);
        danmakus[i].end += danmakus[i].start;
    }

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int end_time = x + y;

        int count = 0;
        for (int j = 0; j < n; j++) {
            if ((danmakus[j].start < end_time && danmakus[j].end > x)) {
                count++;
            }
        }
        printf("%d\n", count);
    }

    free(danmakus);
    return 0;
}