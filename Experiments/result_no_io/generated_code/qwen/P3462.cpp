#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_M 100000

int n, m;
long long weights[MAX_M];
long long capacities[MAX_N];

int compare(const void *a, const void *b) {
    return (*(long long*)b - *(long long*)a);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &capacities[i]);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%lld", &weights[i]);
    }

    qsort(capacities, n, sizeof(long long), compare);
    qsort(weights, m, sizeof(long long), compare);

    int result = 0;
    int j = 0;
    for (int i = 0; i < n && j < m; ++i) {
        while (j < m && weights[j] > capacities[i]) {
            ++j;
        }
        if (j < m) {
            ++result;
            ++j;
        }
    }

    printf("%d\n", result);

    return 0;
}