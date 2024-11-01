#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int P1[MAXN], P2[MAXN], pos[MAXN], dp[MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &P1[i]);
        pos[P1[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", &P2[i]);
    }

    for (int i = 1; i <= n; i++) {
        int idx = pos[P2[i]];
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (dp[mid] < idx) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        dp[lo] = idx;
    }

    int len = 0;
    while (dp[len] != 0) len++;

    printf("%d\n", len);

    return 0;
}