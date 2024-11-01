#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int n, k;
int a[MAXN];
int pos[MAXN];
int cnt[MAXN];

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        pos[i] = i;
    }

    // Sort positions based on the brand of orange juice
    qsort(pos, n, sizeof(int), cmp);

    int distinct_count = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || a[pos[i]] != a[pos[i - 1]]) {
            distinct_count++;
        }
        cnt[pos[i]] = distinct_count;
    }

    // Check if it's possible to have k distinct brands in the first k bottles
    if (distinct_count < k) {
        printf("-1\n");
        return 0;
    }

    // Sort the first k positions
    qsort(pos, k, sizeof(int), cmp);

    int cost = 0;
    for (int i = 0; i < k; i++) {
        if (cnt[pos[i]] != i + 1) {
            cost += abs(pos[i] - i);
        }
    }

    printf("%d\n", cost);
    return 0;
}