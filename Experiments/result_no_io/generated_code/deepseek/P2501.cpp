#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 35005
#define INF 0x3f3f3f3f

int n, a[MAXN], b[MAXN], dp[MAXN], f[MAXN];

int lower_bound(int *arr, int len, int val) {
    int l = 0, r = len - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (arr[mid] < val) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i] - i;
    }
    b[0] = -INF;
    b[n + 1] = INF;
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    int len = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (b[i] >= b[f[len]]) {
            f[++len] = i;
            dp[i] = len;
        } else {
            int pos = lower_bound(b, len + 1, b[i]);
            f[pos] = i;
            dp[i] = pos;
        }
    }
    printf("%d\n", n - len + 1);

    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) {
        if (dp[i] == 1) f[i] = a[i];
        else {
            f[i] = INF;
            for (int j = 0; j < i; j++) {
                if (dp[j] + 1 == dp[i] && b[j] <= b[i]) {
                    int cost = 0;
                    for (int k = j + 1; k < i; k++) {
                        cost += abs(a[k] - (a[j] + (k - j)));
                    }
                    f[i] = f[j] + cost;
                }
            }
        }
    }
    printf("%d\n", f[n]);
    return 0;
}