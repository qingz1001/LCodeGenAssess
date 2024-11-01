#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int up;
    int down;
} Cow;

int compareUp(const void *a, const void *b) {
    return ((Cow *)a)->up - ((Cow *)b)->up;
}

int compareDown(const void *a, const void *b) {
    return ((Cow *)a)->down - ((Cow *)b)->down;
}

int main() {
    int N;
    scanf("%d", &N);
    Cow cows[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cows[i].up, &cows[i].down);
    }

    // Sort cows by their up time
    qsort(cows, N, sizeof(Cow), compareUp);

    // Calculate the total time for climbing up
    int totalUpTime = 0;
    for (int i = 0; i < N; i++) {
        totalUpTime += cows[i].up;
    }

    // Sort cows by their down time
    qsort(cows, N, sizeof(Cow), compareDown);

    // Calculate the total time for climbing down
    int totalDownTime = 0;
    for (int i = 0; i < N; i++) {
        totalDownTime += cows[i].down;
    }

    // The total time is the maximum of the two sums
    int totalTime = totalUpTime > totalDownTime ? totalUpTime : totalDownTime;

    printf("%d\n", totalTime);

    return 0;
}