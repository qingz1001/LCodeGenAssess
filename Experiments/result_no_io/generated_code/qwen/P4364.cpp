#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int difficulty;
} Song;

int compare(const void *a, const void *b) {
    return ((Song *)b)->difficulty - ((Song *)a)->difficulty;
}

void arrangeSongs(int n, double k, int *difficulties, int *result) {
    Song songs[n];
    for (int i = 0; i < n; i++) {
        songs[i].index = i;
        songs[i].difficulty = difficulties[i];
    }

    qsort(songs, n, sizeof(Song), compare);

    int unlockCount = 0;
    int currentIndex = 0;
    while (currentIndex < n) {
        int targetUnlockCount = (currentIndex + k - 1) / k;
        while (unlockCount < targetUnlockCount && currentIndex < n) {
            result[songs[currentIndex].index] = songs[currentIndex].difficulty;
            unlockCount++;
            currentIndex++;
        }
    }
}

int main() {
    int n;
    double k;
    scanf("%d %lf", &n, &k);
    int difficulties[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &difficulties[i]);
    }

    int result[n];
    arrangeSongs(n, k, difficulties, result);

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}