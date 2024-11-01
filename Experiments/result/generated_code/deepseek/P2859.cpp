#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int index;
} Cow;

typedef struct {
    int end;
    int stall;
} Stall;

int compareCows(const void *a, const void *b) {
    Cow *cowA = (Cow *)a;
    Cow *cowB = (Cow *)b;
    return cowA->start - cowB->start;
}

int compareStalls(const void *a, const void *b) {
    Stall *stallA = (Stall *)a;
    Stall *stallB = (Stall *)b;
    return stallA->end - stallB->end;
}

int main() {
    int N;
    scanf("%d", &N);

    Cow cows[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].start, &cows[i].end);
        cows[i].index = i;
    }

    qsort(cows, N, sizeof(Cow), compareCows);

    Stall stalls[N];
    int stallCount = 0;
    int result[N];

    for (int i = 0; i < N; i++) {
        if (stallCount == 0 || stalls[0].end < cows[i].start) {
            // Assign to a new stall
            stalls[0].end = cows[i].end;
            stalls[0].stall = stallCount + 1;
            result[cows[i].index] = stallCount + 1;
            stallCount++;
        } else {
            // Assign to the first available stall
            result[cows[i].index] = stalls[0].stall;
            stalls[0].end = cows[i].end;
        }
        qsort(stalls, stallCount, sizeof(Stall), compareStalls);
    }

    printf("%d\n", stallCount);
    for (int i = 0; i < N; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}