#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 51
#define INF 1e9

int n, c;
int pos[MAX_N], power[MAX_N];
long long dp[MAX_N][MAX_N];

long long min(long long a, long long b) {
    return a < b ? a : b;
}

long long solve(int left, int right) {
    if (left > right) return 0;
    if (dp[left][right] != -1) return dp[left][right];

    long long total_power = 0;
    for (int i = left; i <= right; i++) {
        total_power += power[i];
    }

    long long res = INF;
    if (left == c) {
        res = min(res, solve(left + 1, right) + total_power * (pos[left + 1] - pos[left]));
    } else if (right == c) {
        res = min(res, solve(left, right - 1) + total_power * (pos[right] - pos[right - 1]));
    } else {
        res = min(res, solve(left + 1, right) + total_power * (pos[left + 1] - pos[left]));
        res = min(res, solve(left, right - 1) + total_power * (pos[right] - pos[right - 1]));
    }

    return dp[left][right] = res;
}

int main() {
    scanf("%d %d", &n, &c);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &pos[i], &power[i]);
    }

    memset(dp, -1, sizeof(dp));
    printf("%lld\n", solve(1, n));

    return 0;
}