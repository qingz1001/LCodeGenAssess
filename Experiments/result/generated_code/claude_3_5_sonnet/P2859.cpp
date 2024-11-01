#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 50000

typedef struct {
    int start, end, index;
} Cow;

typedef struct {
    int end;
    int stall;
} Stall;

int cmp_cow(const void *a, const void *b) {
    return ((Cow*)a)->start - ((Cow*)b)->start;
}

int cmp_stall(const void *a, const void *b) {
    return ((Stall*)a)->end - ((Stall*)b)->end;
}

Cow cows[MAXN];
int result[MAXN];
Stall stalls[MAXN];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i].start, &cows[i].end);
        cows[i].index = i;
    }

    qsort(cows, n, sizeof(Cow), cmp_cow);

    int stall_count = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < stall_count; j++) {
            if (stalls[j].end < cows[i].start) {
                stalls[j].end = cows[i].end;
                result[cows[i].index] = stalls[j].stall;
                found = true;
                qsort(stalls, stall_count, sizeof(Stall), cmp_stall);
                break;
            }
        }
        if (!found) {
            stall_count++;
            stalls[stall_count-1].end = cows[i].end;
            stalls[stall_count-1].stall = stall_count;
            result[cows[i].index] = stall_count;
        }
    }

    printf("%d\n", stall_count);
    for (int i = 0; i < n; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}