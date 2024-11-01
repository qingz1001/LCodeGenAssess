#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int n, heights[MAX_N];
int dp[MAX_N], len[MAX_N];

int binary_search(int *arr, int r, int x) {
    int l = 0, m;
    while (l < r) {
        m = l + (r - l) / 2;
        if (arr[m] >= x) r = m;
        else l = m + 1;
    }
    return l;
}

int lis() {
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        int pos = binary_search(dp, max_len, heights[i]);
        dp[pos] = heights[i];
        if (pos == max_len) max_len++;
    }
    return max_len;
}

int min_systems() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        int pos = binary_search(len, count, heights[i]);
        len[pos] = heights[i];
        if (pos == count) count++;
    }
    return count;
}

int main() {
    n = 0;
    while (scanf("%d", &heights[n]) != EOF) n++;

    printf("%d\n", lis());
    printf("%d\n", min_systems());

    return 0;
}