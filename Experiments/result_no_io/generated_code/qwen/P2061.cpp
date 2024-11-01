#include <stdio.h>
#include <stdlib.h>

#define MAXN 40005
#define MAXRANGE 1000000001

typedef struct {
    int start;
    int end;
    int height;
} Building;

int compare(const void *a, const void *b) {
    return ((Building *)a)->start - ((Building *)b)->start;
}

int main() {
    int N;
    scanf("%d", &N);
    Building buildings[MAXN];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d", &buildings[i].start, &buildings[i].end, &buildings[i].height);
    }

    qsort(buildings, N, sizeof(Building), compare);

    int current_height = 0;
    long long total_area = 0;
    int last_end = 0;

    for (int i = 0; i < N; ++i) {
        if (current_height > 0) {
            total_area += (long long)(buildings[i].start - last_end) * current_height;
        }
        if (buildings[i].height > current_height) {
            current_height = buildings[i].height;
        }
        last_end = buildings[i].end;
    }

    printf("%lld\n", total_area);

    return 0;
}