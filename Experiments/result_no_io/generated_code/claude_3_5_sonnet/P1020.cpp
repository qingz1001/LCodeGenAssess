#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int n, heights[MAX_N], dp[MAX_N], len[MAX_N];

int binary_search(int* arr, int r, int x) {
    int l = 1, mid;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (arr[mid] <= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

int lis() {
    int i, length = 1;
    dp[1] = heights[0];
    for (i = 1; i < n; i++) {
        if (heights[i] <= dp[length]) {
            dp[++length] = heights[i];
        } else {
            int pos = binary_search(dp, length, heights[i]);
            dp[pos] = heights[i];
        }
    }
    return length;
}

int min_systems() {
    int i, j, max_len = 0;
    for (i = 0; i < n; i++) {
        len[i] = 1;
        for (j = 0; j < i; j++) {
            if (heights[j] >= heights[i]) {
                len[i] = MAX(len[i], len[j] + 1);
            }
        }
        max_len = MAX(max_len, len[i]);
    }
    return max_len;
}

int main() {
    n = 0;
    while (scanf("%d", &heights[n]) != EOF) {
        n++;
    }

    printf("%d\n", lis());
    printf("%d\n", min_systems());

    return 0;
}