#include <stdio.h>
#include <stdlib.h>

#define MAX_STOPS 20001
#define MAX_GROUPS 50001

typedef struct {
    int start;
    int end;
    int count;
} Group;

Group groups[MAX_GROUPS];
int capacity;
int maxCows;

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
    int K, N;
    scanf("%d %d %d", &K, &N, &capacity);

    for (int i = 0; i < K; i++) {
        scanf("%d %d %d", &groups[i].start, &groups[i].end, &groups[i].count);
    }

    qsort(groups, K, sizeof(Group), compare);

    int currentCows = 0;
    int currentStop = 1;

    for (int i = 0; i < K; i++) {
        if (currentStop <= groups[i].start) {
            currentCows += groups[i].count;
            currentStop = groups[i].end;
            if (currentCows > maxCows) {
                maxCows = currentCows;
            }
            if (currentCows > capacity) {
                currentCows -= groups[i].count;
                currentStop = groups[i].start;
            }
        }
    }

    printf("%d\n", maxCows);

    return 0;
}