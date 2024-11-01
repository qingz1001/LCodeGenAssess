#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_TIME 1000000

typedef struct {
    int start;
    int end;
    int id;
} Cow;

typedef struct {
    int end_time;
    int stall_id;
} Stall;

int cmp(const void *a, const void *b) {
    Cow *c1 = (Cow *)a;
    Cow *c2 = (Cow *)b;
    return c1->start - c2->start;
}

int main() {
    int N;
    Cow cows[MAX_N];
    Stall stalls[MAX_N];
    int stall_count = 0;
    int stall_assignments[MAX_N];

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].start, &cows[i].end);
        cows[i].id = i;
    }

    qsort(cows, N, sizeof(Cow), cmp);

    for (int i = 0; i < N; i++) {
        int assigned = 0;
        for (int j = 0; j < stall_count; j++) {
            if (stalls[j].end_time < cows[i].start) {
                stalls[j].end_time = cows[i].end;
                stall_assignments[cows[i].id] = stalls[j].stall_id;
                assigned = 1;
                break;
            }
        }
        if (!assigned) {
            stalls[stall_count].end_time = cows[i].end;
            stalls[stall_count].stall_id = stall_count + 1;
            stall_assignments[cows[i].id] = stalls[stall_count].stall_id;
            stall_count++;
        }
    }

    printf("%d\n", stall_count);
    for (int i = 0; i < N; i++) {
        printf("%d\n", stall_assignments[i]);
    }

    return 0;
}