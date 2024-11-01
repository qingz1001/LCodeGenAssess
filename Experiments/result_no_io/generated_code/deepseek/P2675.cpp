#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int N;
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    qsort(arr, N, sizeof(int), compare);

    int result = 0;
    for (int i = 0; i < N; i++) {
        result = (result + arr[i] * (N - i)) % MOD;
    }

    printf("%d\n", result);

    free(arr);
    return 0;
}