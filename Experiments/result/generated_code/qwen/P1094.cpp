#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minGroups(int W, int n, int prices[]) {
    qsort(prices, n, sizeof(int), compare);

    int groups = 0;
    for (int i = 0; i < n; ) {
        if (prices[i] + prices[n-1] <= W) {
            i++;
        }
        n--;
        groups++;
    }

    return groups;
}

int main() {
    int W, n;
    scanf("%d %d", &W, &n);
    int prices[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    printf("%d\n", minGroups(W, n, prices));

    return 0;
}