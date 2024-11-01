#include <stdio.h>
#include <stdlib.h>

#define MOD 92084931

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, M;
    scanf("%d %d", &n, &M);
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    qsort(arr, n, sizeof(int), compare);

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > M) {
            count++;
        } else {
            break;
        }
    }

    printf("%d\n", count % MOD);

    free(arr);
    return 0;
}