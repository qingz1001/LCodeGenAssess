#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20001
#define MAX_K 50000

typedef struct {
    int start, end, cows;
} Group;

Group groups[MAX_K];
int diff[MAX_N];

int cmp(const void *a, const void *b) {
    return ((Group*)a)->end - ((Group*)b)->end;
}

int main() {
    int K, N, C;
    scanf("%d %d %d", &K, &N, &C);

    for (int i = 0; i < K; i++) {
        scanf("%d %d %d", &groups[i].start, &groups[i].end, &groups[i].cows);
    }

    qsort(groups, K, sizeof(Group), cmp);

    memset(diff, 0, sizeof(diff));

    int total_cows = 0;
    for (int i = 0; i < K; i++) {
        int available = C;
        for (int j = groups[i].start; j < groups[i].end; j++) {
            available = (available < C - diff[j]) ? available : C - diff[j];
        }

        int picked = (available < groups[i].cows) ? available : groups[i].cows;
        total_cows += picked;

        diff[groups[i].start] += picked;
        diff[groups[i].end] -= picked;

        for (int j = groups[i].start + 1; j < groups[i].end; j++) {
            diff[j] += diff[j-1];
        }
    }

    printf("%d\n", total_cows);

    return 0;
}