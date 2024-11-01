#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20001
#define MAXK 50000

typedef struct {
    int start, end, count;
} Group;

Group groups[MAXK];
int diff[MAXN];

int cmp(const void *a, const void *b) {
    return ((Group*)a)->end - ((Group*)b)->end;
}

int main() {
    int K, N, C;
    scanf("%d %d %d", &K, &N, &C);

    for (int i = 0; i < K; i++) {
        scanf("%d %d %d", &groups[i].start, &groups[i].end, &groups[i].count);
    }

    qsort(groups, K, sizeof(Group), cmp);

    memset(diff, 0, sizeof(diff));

    int total = 0;
    for (int i = 0; i < K; i++) {
        int capacity = C;
        for (int j = groups[i].start; j < groups[i].end; j++) {
            capacity -= diff[j];
            if (capacity < 0) capacity = 0;
        }

        int taken = groups[i].count < capacity ? groups[i].count : capacity;
        total += taken;

        diff[groups[i].start] += taken;
        diff[groups[i].end] -= taken;
    }

    printf("%d\n", total);

    return 0;
}