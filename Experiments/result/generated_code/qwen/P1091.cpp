#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int *heights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int *left = (int *)malloc(n * sizeof(int));
    int *right = (int *)malloc(n * sizeof(int));

    left[0] = 1;
    for (int i = 1; i < n; i++) {
        left[i] = 1;
        for (int j = 0; j < i; j++) {
            if (heights[i] > heights[j]) {
                left[i] = max(left[i], left[j] + 1);
            }
        }
    }

    right[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) {
        right[i] = 1;
        for (int j = n - 1; j > i; j--) {
            if (heights[i] > heights[j]) {
                right[i] = max(right[i], right[j] + 1);
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        result = max(result, left[i] + right[i] - 1);
    }

    printf("%d\n", n - result);

    free(heights);
    free(left);
    free(right);

    return 0;
}