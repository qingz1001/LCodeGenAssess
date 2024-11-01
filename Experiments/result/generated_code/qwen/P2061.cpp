#include <stdio.h>
#include <stdlib.h>

#define MAX_N 40000
#define MAX_A 1000000000

typedef struct {
    int a;
    int b;
    int h;
} Building;

int compare(const void *a, const void *b) {
    return ((Building *)a)->a - ((Building *)b)->a;
}

int main() {
    int N;
    scanf("%d", &N);
    Building buildings[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d", &buildings[i].a, &buildings[i].b, &buildings[i].h);
    }

    qsort(buildings, N, sizeof(Building), compare);

    long long total_area = 0;
    int current_height = 0;
    int prev_end = 0;

    for (int i = 0; i < N; ++i) {
        int start = buildings[i].a;
        int end = buildings[i].b;
        int height = buildings[i].h;

        if (start > prev_end) {
            total_area += (long long)(start - prev_end) * current_height;
        }

        if (height > current_height) {
            total_area += (long long)(end - start) * (height - current_height);
        }

        current_height = height;
        prev_end = end;
    }

    total_area += (long long)(prev_end - buildings[N-1].b) * current_height;

    printf("%lld\n", total_area);

    return 0;
}