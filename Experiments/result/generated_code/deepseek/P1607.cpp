#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define MAX_K 50000
#define MAX_C 100

typedef struct {
    int start, end, count;
} Group;

int compare(const void *a, const void *b) {
    Group *groupA = (Group *)a;
    Group *groupB = (Group *)b;
    if (groupA->end == groupB->end) {
        return groupA->start - groupB->start;
    }
    return groupA->end - groupB->end;
}

int main() {
    int K, N, C;
    scanf("%d %d %d", &K, &N, &C);

    Group groups[MAX_K];
    for (int i = 0; i < K; i++) {
        scanf("%d %d %d", &groups[i].start, &groups[i].end, &groups[i].count);
    }

    qsort(groups, K, sizeof(Group), compare);

    int capacity[MAX_N + 1] = {0};
    int totalCows = 0;

    for (int i = 0; i < K; i++) {
        int start = groups[i].start;
        int end = groups[i].end;
        int count = groups[i].count;

        int available = 0;
        for (int j = start; j < end; j++) {
            if (capacity[j] < C) {
                available += C - capacity[j];
            }
        }

        int canTake = (available < count) ? available : count;
        totalCows += canTake;

        for (int j = start; j < end; j++) {
            capacity[j] += canTake;
        }
    }

    printf("%d\n", totalCows);

    return 0;
}