#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500005

int n, k;
int a[MAX_N];
int last[MAX_N];
int used[MAX_N];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    memset(last, 0, sizeof(last));
    memset(used, 0, sizeof(used));

    int cost = 0;
    int distinct = 0;

    for (int i = 1; i <= n; i++) {
        if (!used[a[i]]) {
            distinct++;
            used[a[i]] = 1;
        }

        if (distinct == k) {
            for (int j = 1; j <= k; j++) {
                cost += i - last[a[j]] - 1;
                last[a[j]] = j;
            }
            printf("%d\n", cost);
            return 0;
        }

        last[a[i]] = i;
    }

    printf("-1\n");
    return 0;
}