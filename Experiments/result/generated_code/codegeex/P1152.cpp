#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int *diffs = (int *)calloc(n - 1, sizeof(int));
    for (int i = 1; i < n; i++) {
        int diff = abs(arr[i] - arr[i - 1]);
        if (diff < n) {
            diffs[diff] = 1;
        }
    }

    int flag = 1;
    for (int i = 1; i < n; i++) {
        if (diffs[i] != 1) {
            flag = 0;
            break;
        }
    }

    if (flag) {
        printf("Jolly\n");
    } else {
        printf("Not jolly\n");
    }

    free(arr);
    free(diffs);

    return 0;
}