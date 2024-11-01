#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define MAX_K 50000
#define MAX_C 100

typedef struct {
    int start;
    int end;
    int count;
} CowGroup;

int compare(const void *a, const void *b) {
    return ((CowGroup *)a)->end - ((CowGroup *)b)->end;
}

int main() {
    int K, N, C;
    scanf("%d %d %d", &K, &N, &C);

    CowGroup groups[MAX_K];
    for (int i = 0; i < K; ++i) {
        scanf("%d %d %d", &groups[i].start, &groups[i].end, &groups[i].count);
    }

    qsort(groups, K, sizeof(CowGroup), compare);

    int max_cows = 0;
    for (int i = 0; i < K; ++i) {
        if (groups[i].count > C) {
            max_cows += C;
            groups[i].count -= C;
        } else {
            max_cows += groups[i].count;
            groups[i].count = 0;
        }
    }

    printf("%d\n", max_cows);

    return 0;
}