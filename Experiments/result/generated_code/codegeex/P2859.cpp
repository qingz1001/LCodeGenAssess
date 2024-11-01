#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
    int stall;
} Cow;

int compare(const void *a, const void *b) {
    Cow *cowA = (Cow *)a;
    Cow *cowB = (Cow *)b;
    if (cowA->end == cowB->end) {
        return cowA->start - cowB->start;
    }
    return cowA->end - cowB->end;
}

int main() {
    int N;
    scanf("%d", &N);

    Cow cows[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].start, &cows[i].end);
        cows[i].stall = -1;
    }

    qsort(cows, N, sizeof(Cow), compare);

    int *stallEnds = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        stallEnds[i] = 0;
    }

    int minStalls = 0;
    for (int i = 0; i < N; i++) {
        int stall = -1;
        for (int j = 0; j < minStalls; j++) {
            if (stallEnds[j] <= cows[i].start) {
                stall = j;
                break;
            }
        }
        if (stall == -1) {
            stall = minStalls++;
        }
        cows[i].stall = stall;
        stallEnds[stall] = cows[i].end;
    }

    printf("%d\n", minStalls);
    for (int i = 0; i < N; i++) {
        printf("%d\n", cows[i].stall + 1);
    }

    free(stallEnds);
    return 0;
}