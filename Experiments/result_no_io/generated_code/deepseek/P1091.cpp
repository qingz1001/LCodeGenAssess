#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int main() {
    int n;
    int heights[MAXN];
    int lis[MAXN], lds[MAXN];
    int i, j, max_len = 0;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    // Calculate Longest Increasing Subsequence (LIS)
    for (i = 0; i < n; i++) {
        lis[i] = 1;
        for (j = 0; j < i; j++) {
            if (heights[j] < heights[i] && lis[j] + 1 > lis[i]) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    // Calculate Longest Decreasing Subsequence (LDS)
    for (i = n - 1; i >= 0; i--) {
        lds[i] = 1;
        for (j = n - 1; j > i; j--) {
            if (heights[j] < heights[i] && lds[j] + 1 > lds[i]) {
                lds[i] = lds[j] + 1;
            }
        }
    }

    // Find the maximum length of the combined LIS and LDS
    for (i = 0; i < n; i++) {
        if (lis[i] + lds[i] - 1 > max_len) {
            max_len = lis[i] + lds[i] - 1;
        }
    }

    // The minimum number of students to remove is the total number minus the maximum length
    printf("%d\n", n - max_len);

    return 0;
}