#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(long long *)a - *(long long *)b);
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    long long *a = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    qsort(a, n, sizeof(long long), compare);

    int *used = (int *)calloc(n, sizeof(int));
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            ans++;
            long long current = a[i];
            for (int j = i + 1; j < n; j++) {
                if (a[j] == current * k) {
                    used[j] = 1;
                    break;
                }
            }
        }
    }

    printf("%d\n", ans);

    free(a);
    free(used);
    return 0;
}