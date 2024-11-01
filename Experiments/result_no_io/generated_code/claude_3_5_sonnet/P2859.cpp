#include <stdio.h>
#include <stdlib.h>

#define MAXN 50000

typedef struct {
    int start, end, index;
} Cow;

typedef struct {
    int end, stall;
} Stall;

int cmp_cow(const void *a, const void *b) {
    return ((Cow *)a)->start - ((Cow *)b)->start;
}

int cmp_stall(const void *a, const void *b) {
    return ((Stall *)a)->end - ((Stall *)b)->end;
}

Cow cows[MAXN];
Stall stalls[MAXN];
int result[MAXN];

int main() {
    int n, i, stall_count = 0;
    
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d", &cows[i].start, &cows[i].end);
        cows[i].index = i;
    }
    
    qsort(cows, n, sizeof(Cow), cmp_cow);
    
    for (i = 0; i < n; i++) {
        int j;
        for (j = 0; j < stall_count; j++) {
            if (stalls[j].end < cows[i].start) {
                stalls[j].end = cows[i].end;
                result[cows[i].index] = stalls[j].stall;
                break;
            }
        }
        if (j == stall_count) {
            stall_count++;
            stalls[j].end = cows[i].end;
            stalls[j].stall = stall_count;
            result[cows[i].index] = stall_count;
        }
        qsort(stalls, stall_count, sizeof(Stall), cmp_stall);
    }
    
    printf("%d\n", stall_count);
    for (i = 0; i < n; i++) {
        printf("%d\n", result[i]);
    }
    
    return 0;
}