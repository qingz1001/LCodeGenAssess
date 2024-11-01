#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 70
#define INF 0x3f3f3f3f

int n;
int h[MAX_N], t[MAX_N];
int dp[1 << MAX_N];
int sum_t[1 << MAX_N], max_h[1 << MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void init() {
    for (int s = 1; s < (1 << n); s++) {
        for (int i = 0; i < n; i++) {
            if (s & (1 << i)) {
                sum_t[s] += t[i];
                max_h[s] = max(max_h[s], h[i]);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &h[i], &t[i]);
    }

    init();

    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int s = 1; s < (1 << n); s++) {
        for (int s0 = s; s0; s0 = (s0 - 1) & s) {
            dp[s] = min(dp[s], max(dp[s ^ s0], max_h[s0]));
        }
    }

    int ans = INF;
    for (int s1 = 1; s1 < (1 << n) - 1; s1++) {
        for (int s2 = 1; s2 < (1 << n) - 1; s2++) {
            if (s1 & s2) continue;
            int s3 = ((1 << n) - 1) ^ s1 ^ s2;
            if (s3 == 0) continue;
            int height = dp[s1] + dp[s2] + dp[s3];
            int width = max(max(sum_t[s1], sum_t[s2]), sum_t[s3]);
            ans = min(ans, height * width);
        }
    }

    printf("%d\n", ans);

    return 0;
}