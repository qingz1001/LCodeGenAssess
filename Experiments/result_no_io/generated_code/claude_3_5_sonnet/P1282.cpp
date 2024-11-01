#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n, a, b;
    int sum1 = 0, sum2 = 0;
    int diff[MAX_N];
    int rotations = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        sum1 += a;
        sum2 += b;
        diff[i] = b - a;
    }

    int diff_sum = sum2 - sum1;

    if (diff_sum % 2 != 0) {
        printf("0\n");
        return 0;
    }

    int target = diff_sum / 2;

    for (int i = 0; i < n; i++) {
        if (diff[i] > 0 && target > 0) {
            rotations += (diff[i] <= target) ? 1 : 0;
            target -= min(diff[i], target);
        }
    }

    printf("%d\n", rotations);

    return 0;
}