#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long min_cost = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            min_cost += arr[i];
            arr[i + 1] = arr[i];
        } else {
            min_cost += arr[i + 1];
        }
    }

    printf("%lld\n", min_cost);

    free(arr);
    return 0;
}