#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int *diff = (int*)malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        diff[i] = abs(a[i + 1] - a[i]);
    }

    int *found = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        if (diff[i] < n) {
            found[diff[i]] = 1;
        }
    }

    int isJolly = 1;
    for (int i = 1; i < n; i++) {
        if (found[i] != 1) {
            isJolly = 0;
            break;
        }
    }

    if (isJolly) {
        printf("Jolly\n");
    } else {
        printf("Not jolly\n");
    }

    free(a);
    free(diff);
    free(found);
    return 0;
}