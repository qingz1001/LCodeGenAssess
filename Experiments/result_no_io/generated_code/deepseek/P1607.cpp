#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define MAX_K 50000
#define MAX_C 100

typedef struct {
    int start, end, count;
} Group;

int compare(const void *a, const void *b) {
    Group *g1 = (Group *)a;
    Group *g2 = (Group *)b;
    if (g1->end != g2->end) return g1->end - g2->end;
    return g1->start - g2->start;
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
    int total_cows = 0;

    for (int i = 0; i < K; i++) {
        int start = groups[i].start;
        int end = groups[i].end;
        int count = groups[i].count;

        int available_capacity = 0;
        for (int j = start; j < end; j++) {
            if (capacity[j] < C) {
                available_capacity += (C - capacity[j]);
            }
        }

        int cows_to_board = (available_capacity < count) ? available_capacity : count;
        total_cows += cows_to_board;

        for (int j = start; j < end && cows_to_board > 0; j++) {
            int space_left = C - capacity[j];
            int cows_on_this_stop = (cows_to_board < space_left) ? cows_to_board : space_left;
            capacity[j] += cows_on_this_stop;
            cows_to_board -= cows_on_this_stop;
        }
    }

    printf("%d\n", total_cows);

    return 0;
}