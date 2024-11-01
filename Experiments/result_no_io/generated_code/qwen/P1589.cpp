#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_E 1000000000

typedef struct {
    int start;
    int end;
} Road;

int compare(const void *a, const void *b) {
    return ((Road *)a)->start - ((Road *)b)->start;
}

int main() {
    int n, L;
    scanf("%d %d", &n, &L);
    Road roads[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &roads[i].start, &roads[i].end);
    }

    qsort(roads, n, sizeof(Road), compare);

    int boards = 0;
    int current_end = 0;
    for (int i = 0; i < n; ++i) {
        if (roads[i].start > current_end) {
            boards++;
            current_end = roads[i].start + L - 1;
        }
        current_end = current_end > roads[i].end ? current_end : roads[i].end;
    }

    printf("%d\n", boards);
    return 0;
}