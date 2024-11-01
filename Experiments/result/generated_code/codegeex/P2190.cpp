#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, x, y, z, max = 0;
    scanf("%d %d", &n, &m);

    int *arr = (int*)calloc(n + 1, sizeof(int));

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        if (x < y) {
            arr[x] += z;
            arr[y] -= z;
        } else {
            arr[x] += z;
            arr[y] -= z;
            arr[n] -= z;
            arr[1] += z;
        }
    }

    for (int i = 1; i <= n; i++) {
        arr[i] += arr[i - 1];
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    printf("%d\n", (max + 35) / 36);

    free(arr);
    return 0;
}