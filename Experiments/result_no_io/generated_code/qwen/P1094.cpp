#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30000
#define MAX_W 200

int n, w;
int prices[MAX_N];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    scanf("%d %d", &w, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    // Sort the prices in ascending order
    qsort(prices, n, sizeof(int), (int (*)(const void *, const void *))strcmp);

    int dp[MAX_W + 1];
    for (int i = 0; i <= w; i++) {
        dp[i] = i / w + 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = w; j >= prices[i]; j--) {
            dp[j] = min(dp[j], dp[j - prices[i]] + 1);
        }
    }

    printf("%d\n", dp[w]);

    return 0;
}