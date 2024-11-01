#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, C;
    scanf("%d %d", &N, &C);
    long long *arr = (long long *)malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++) {
        scanf("%lld", &arr[i]);
    }

    long long count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (arr[j] == arr[i] - C) {
                count++;
            }
        }
    }

    printf("%lld\n", count);

    free(arr);
    return 0;
}