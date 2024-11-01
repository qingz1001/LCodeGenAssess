#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000000
#define MAXM 1000

typedef struct {
    int start;
    int end;
} Poster;

int compare(const void *a, const void *b) {
    Poster *p1 = (Poster *)a;
    Poster *p2 = (Poster *)b;
    return p1->start - p2->start;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Poster posters[MAXM];
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &posters[i].start, &posters[i].end);
    }

    // 按海报的起始位置排序
    qsort(posters, M, sizeof(Poster), compare);

    int visible_count = 0;
    int current_end = 0;

    for (int i = 0; i < M; i++) {
        if (posters[i].start > current_end) {
            visible_count++;
            current_end = posters[i].end;
        } else if (posters[i].end > current_end) {
            current_end = posters[i].end;
        }
    }

    printf("%d\n", visible_count);

    return 0;
}