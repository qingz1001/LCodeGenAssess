#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int up;
    int down;
} Cow;

int compare(const void *a, const void *b) {
    Cow *cowA = (Cow *)a;
    Cow *cowB = (Cow *)b;
    return (cowA->up + cowA->down) - (cowB->up + cowB->down);
}

int main() {
    int N;
    scanf("%d", &N);
    Cow cows[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].up, &cows[i].down);
    }

    qsort(cows, N, sizeof(Cow), compare);

    int totalUpTime = 0;
    int totalDownTime = 0;
    int maxMountainTime = 0;

    for (int i = 0; i < N; i++) {
        totalUpTime += cows[i].up;
        maxMountainTime = (maxMountainTime > totalDownTime) ? maxMountainTime : totalDownTime;
        totalDownTime += cows[i].down;
    }

    int result = totalUpTime + totalDownTime + maxMountainTime;
    printf("%d\n", result);

    return 0;
}