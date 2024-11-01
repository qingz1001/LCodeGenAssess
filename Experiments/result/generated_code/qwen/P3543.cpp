#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    int *heights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int positive_sum = 0, negative_sum = 0;
    for (int i = 0; i < n; i++) {
        if (heights[i] > 0) {
            positive_sum += heights[i];
        } else {
            negative_sum -= heights[i];
        }
    }

    if (positive_sum % a != 0 || negative_sum % b != 0) {
        printf("-1\n");
        free(heights);
        return 0;
    }

    int ops = 0;
    while (positive_sum > 0 || negative_sum < 0) {
        if (positive_sum >= a) {
            positive_sum -= a;
            ops++;
        } else {
            positive_sum += b;
            ops++;
        }
        if (negative_sum <= -b) {
            negative_sum += b;
            ops++;
        } else {
            negative_sum -= a;
            ops++;
        }
    }

    printf("%d\n", ops);
    free(heights);
    return 0;
}