#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, a, b;
    int s1 = 0, s2 = 0;
    int diff[MAX_N];
    int total_diff = 0;
    int rotations = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        s1 += a;
        s2 += b;
        diff[i] = a - b;
        total_diff += abs(diff[i]);
    }

    int target_diff = abs(s1 - s2);

    if (target_diff % 2 == 0) {
        target_diff /= 2;
        for (int i = 0; i < n; i++) {
            if (diff[i] > 0 && target_diff > 0) {
                rotations += 1;
                target_diff -= diff[i];
            } else if (diff[i] < 0 && target_diff < 0) {
                rotations += 1;
                target_diff += abs(diff[i]);
            }
            if (target_diff == 0) break;
        }
    } else {
        rotations = -1;
    }

    printf("%d\n", rotations);

    return 0;
}