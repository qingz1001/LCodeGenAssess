#include <stdio.h>
#include <stdlib.h>

#define MAX_N 9

int main() {
    int n;
    scanf("%d", &n);

    if (n == 1) {
        printf("1\n");
        printf("1\n");
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}