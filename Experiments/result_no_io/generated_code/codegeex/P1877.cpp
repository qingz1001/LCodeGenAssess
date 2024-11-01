#include <stdio.h>
#include <stdbool.h>

#define MAX_N 51
#define MAX_LEVEL 1001

int n, beginLevel, maxLevel;
int changes[MAX_N];

bool canReachVolume(int currentVolume, int songIndex) {
    if (songIndex == n) {
        return currentVolume >= 0 && currentVolume <= maxLevel;
    }
    int nextVolume = currentVolume + changes[songIndex];
    if (nextVolume >= 0 && nextVolume <= maxLevel && canReachVolume(nextVolume, songIndex + 1)) {
        return true;
    }
    nextVolume = currentVolume - changes[songIndex];
    if (nextVolume >= 0 && nextVolume <= maxLevel && canReachVolume(nextVolume, songIndex + 1)) {
        return true;
    }
    return false;
}

int main() {
    scanf("%d %d %d", &n, &beginLevel, &maxLevel);
    for (int i = 0; i < n; i++) {
        scanf("%d", &changes[i]);
    }

    if (canReachVolume(beginLevel, 0)) {
        printf("%d\n", maxLevel);
    } else {
        printf("-1\n");
    }

    return 0;
}