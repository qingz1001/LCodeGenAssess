#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_M 100005

typedef struct {
    int start;
    int end;
} Barrage;

int compare(const void *a, const void *b) {
    return ((Barrage *)a)->start - ((Barrage *)b)->start;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Barrage barrages[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &barrages[i].start, &barrages[i].end);
    }

    qsort(barrages, n, sizeof(Barrage), compare);

    int queries[MAX_M][2];
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }

    for (int i = 0; i < m; ++i) {
        int left = queries[i][0];
        int right = queries[i][0] + queries[i][1];

        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (left <= barrages[j].start && barrages[j].end <= right) {
                count++;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}