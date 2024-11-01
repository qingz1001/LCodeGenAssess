#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

typedef struct {
    int s, e;
} Road;

int compare(const void *a, const void *b) {
    return ((Road *)a)->s - ((Road *)b)->s;
}

int main() {
    int n, L;
    scanf("%d %d", &n, &L);
    Road roads[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &roads[i].s, &roads[i].e);
    }

    qsort(roads, n, sizeof(Road), compare);

    int boards = 0;
    int current_end = 0;
    for (int i = 0; i < n; i++) {
        if (roads[i].s > current_end) {
            boards++;
            current_end = roads[i].s + L - 1;
        }
        if (roads[i].e > current_end) {
            current_end = roads[i].e;
        }
    }

    printf("%d\n", boards);
    return 0;
}