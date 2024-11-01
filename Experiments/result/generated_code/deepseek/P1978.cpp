#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    long long *arr = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    qsort(arr, n, sizeof(long long), compare);

    int *used = (int *)calloc(n, sizeof(int));
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            ans++;
            long long current = arr[i];
            for (int j = i + 1; j < n; j++) {
                if (arr[j] == current * k) {
                    used[j] = 1;
                    current = arr[j];
                }
            }
        }
    }

    printf("%d\n", ans);

    free(arr);
    free(used);
    return 0;
}