#include <stdio.h>
#include <stdlib.h>

int L, N, M;
int rocks[50005];

int canAchieveMinDistance(int minDistance) {
    int removed = 0;
    int lastRock = 0;

    for (int i = 0; i < N; i++) {
        if (rocks[i] - lastRock < minDistance) {
            removed++;
        } else {
            lastRock = rocks[i];
        }
    }

    if (L - lastRock < minDistance) {
        removed++;
    }

    return removed <= M;
}

int main() {
    scanf("%d %d %d", &L, &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &rocks[i]);
    }

    int left = 1, right = L;
    int result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canAchieveMinDistance(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}