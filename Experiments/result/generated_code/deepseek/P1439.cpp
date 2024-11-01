#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int P1[MAXN], P2[MAXN];
    int pos1[MAXN], pos2[MAXN];

    for (int i = 1; i <= n; i++) {
        scanf("%d", &P1[i]);
        pos1[P1[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &P2[i]);
        pos2[P2[i]] = i;
    }

    int dp[MAXN];
    for (int i = 0; i <= n; i++) {
        dp[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int idx = pos2[P1[i]];
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (dp[mid] < idx) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        dp[lo + 1] = idx;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] != 0) {
            ans = i;
        }
    }

    printf("%d\n", ans);
    return 0;
}