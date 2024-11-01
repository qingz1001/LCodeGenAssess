#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500000
#define MAX_D 2000
#define INF 0x3f3f3f3f

typedef long long ll;

int n, d, k;
int x[MAX_N + 1], s[MAX_N + 1];
ll dp[MAX_N + 1];

int check(int g) {
    memset(dp, 0xc0, sizeof(dp));
    dp[0] = 0;
    int j = 0;
    for (int i = 1; i <= n; i++) {
        while (j < i && x[i] - x[j] > d + g) j++;
        for (int k = j; k < i; k++) {
            if (x[i] - x[k] >= d - g || g >= d)
                dp[i] = (dp[i] > dp[k] + s[i]) ? dp[i] : dp[k] + s[i];
        }
    }
    ll maxScore = 0;
    for (int i = 1; i <= n; i++)
        maxScore = (maxScore > dp[i]) ? maxScore : dp[i];
    return maxScore >= k;
}

int main() {
    scanf("%d%d%d", &n, &d, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &x[i], &s[i]);

    int left = 0, right = MAX_D + d, mid;
    int ans = -1;
    while (left <= right) {
        mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", ans);
    return 0;
}