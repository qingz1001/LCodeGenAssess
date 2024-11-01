#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int *left_count = (int *)malloc(n * sizeof(int));
    int *right_count = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        left_count[i] = 0;
        right_count[i] = 0;
    }

    // Count the number of elements less than a[i] to the left of i
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                left_count[i]++;
            }
        }
    }

    // Count the number of elements greater than a[i] to the right of i
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[i]) {
                right_count[i]++;
            }
        }
    }

    int thair_count = 0;
    for (int j = 1; j < n - 1; j++) {
        thair_count += left_count[j] * right_count[j];
    }

    printf("%d\n", thair_count);

    free(a);
    free(left_count);
    free(right_count);

    return 0;
}