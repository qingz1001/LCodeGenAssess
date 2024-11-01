#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int n, k;
int a[MAXN];
int pos[MAXN];
int count[MAXN];

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

    int distinct = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || a[pos[i]] != a[pos[i - 1]]) {
            distinct++;
        }
        count[pos[i]] = distinct;
    }

    // Check if we can have k distinct brands in the first k bottles
    int required_distinct = 0;
    for (int i = 0; i < k; i++) {
        if (i == 0 || count[i] != count[i - 1]) {
            required_distinct++;
        }
    }

    if (required_distinct < k) {
        printf("-1\n");
        return 0;
    }

    // Calculate the minimum cost to make the first k bottles distinct
    int cost = 0;
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (count[j] == count[i]) {
                cost++;
            }
        }
    }

    printf("%d\n", cost);
    return 0;
}