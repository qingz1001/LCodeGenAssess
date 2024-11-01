#include <stdio.h>
#include <stdlib.h>

int L, N, M;
int rocks[50005];

int isPossible(int min_dist) {
    int removed = 0;
    int last_rock = 0;

    for (int i = 0; i < N; i++) {
        if (rocks[i] - last_rock < min_dist) {
            removed++;
        } else {
            last_rock = rocks[i];
        }
    }

    if (L - last_rock < min_dist) {
        removed++;
    }

    return removed <= M;
}

int main() {
    scanf("%d %d %d", &L, &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &rocks[i]);
    }

    int left = 0, right = L;
    int result = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (isPossible(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}