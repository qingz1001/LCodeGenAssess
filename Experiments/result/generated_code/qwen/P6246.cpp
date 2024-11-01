#include <stdio.h>
#include <stdlib.h>

#define MAXN 500001
#define INF 1e9

int n, m;
int a[MAXN];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long min_distance(int *arr, int size, int k) {
    long long total = 0;
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            total += abs(arr[i] - arr[k / 2]);
        } else {
            total += abs(arr[i] - arr[(k + i - 1) / 2]);
        }
    }
    return total;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    long long best = INF;
    for (int i = m - 1; i <= n; i++) {
        best = fmin(best, min_distance(a, n, i));
    }

    printf("%lld\n", best);

    return 0;
}