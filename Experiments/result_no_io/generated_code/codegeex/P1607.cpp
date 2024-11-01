#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int count;
} Group;

int compare(const void *a, const void *b) {
    Group *groupA = (Group *)a;
    Group *groupB = (Group *)b;
    if (groupA->end != groupB->end) {
        return groupA->end - groupB->end;
    } else {
        return groupA->start - groupB->start;
    }
}

int main() {
    int K, N, C;
    scanf("%d %d %d", &K, &N, &C);

    Group groups[K];
    for (int i = 0; i < K; i++) {
        scanf("%d %d %d", &groups[i].start, &groups[i].end, &groups[i].count);
    }

    qsort(groups, K, sizeof(Group), compare);

    int shuttle = C;
    int maxCows = 0;
    int i = 0;

    while (i < K && shuttle > 0) {
        int currentCows = 0;
        while (i < K && groups[i].start <= groups[i].end && shuttle > 0) {
            if (groups[i].count <= shuttle) {
                currentCows += groups[i].count;
                shuttle -= groups[i].count;
            } else {
                currentCows += shuttle;
                shuttle = 0;
            }
            i++;
        }
        maxCows = (maxCows > currentCows) ? maxCows : currentCows;
        shuttle = C;
    }

    printf("%d\n", maxCows);
    return 0;
}