#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int barns[MAXN];
int N, M;

// Check if it's possible to place all cows with at least 'dist' distance apart
int canPlaceCows(int dist) {
    int count = 1; // Place the first cow in the first barn
    int last_position = barns[0];

    for (int i = 1; i < N; i++) {
        if (barns[i] - last_position >= dist) {
            count++;
            last_position = barns[i];
        }
        if (count == M) return 1;
    }

    return 0;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &barns[i]);
    }

    // Sort the barn positions
    qsort(barns, N, sizeof(int), (void*)cmp);

    int left = 0, right = barns[N-1] - barns[0], result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canPlaceCows(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", result);
    return 0;
}