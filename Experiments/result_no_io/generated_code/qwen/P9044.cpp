#include <stdio.h>
#include <stdlib.h>

#define MAXN 2005
#define MAXA 121

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int a[MAXN];
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }

    // Sort the array in non-decreasing order
    qsort(a + 1, n, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // Calculate the minimum number of gifts needed
    int min_gifts = 0;
    for (int i = 1; i <= n; ++i) {
        if (min_gifts >= k) break;
        if (i == n || a[i] != a[i + 1]) {
            ++min_gifts;
        }
    }

    printf("%d\n", min_gifts);

    return 0;
}