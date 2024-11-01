#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    int heights[MAXN];
    int lis[MAXN], lds[MAXN];
    int i, j;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    // Calculate Longest Increasing Subsequence (LIS)
    for (i = 0; i < n; i++) {
        lis[i] = 1;
        for (j = 0; j < i; j++) {
            if (heights[j] < heights[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }

    // Calculate Longest Decreasing Subsequence (LDS)
    for (i = n - 1; i >= 0; i--) {
        lds[i] = 1;
        for (j = n - 1; j > i; j--) {
            if (heights[j] < heights[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }

    // Find the maximum k such that there exists i with LIS[i] + LDS[i] - 1 = k
    int max_k = 0;
    for (i = 0; i < n; i++) {
        max_k = max(max_k, lis[i] + lds[i] - 1);
    }

    // The minimum number of students to remove is n - max_k
    printf("%d\n", n - max_k);

    return 0;
}