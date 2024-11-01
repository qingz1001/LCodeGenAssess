#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int min_cost = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > min_cost) {
            min_cost = arr[i];
        }
    }

    printf("%d\n", min_cost);

    free(arr);
    return 0;
}