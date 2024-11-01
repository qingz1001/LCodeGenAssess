#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 151
#define MAX_M 14
#define INF 0x3f3f3f3f

int N, V[MAX_N], A[MAX_N];
int dp[MAX_N][MAX_N][MAX_M][MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int solve(int l, int r, int ll, int rr) {
    if (l > r) return 0;
    if (dp[l][r][ll][rr] != -INF) return dp[l][r][ll][rr];

    int res = -INF;
    // 不删除
    res = max(res, solve(l + 1, r, 0, rr));
    res = max(res, solve(l, r - 1, ll, 0));

    // 删除左边
    if (ll == 0 || abs(A[l - 1] - A[l]) == 1) {
        for (int i = l + 1; i <= r; i++) {
            if (abs(A[i - 1] - A[i]) != 1) break;
            if (i > l + 1 && A[i - 1] > A[i - 2] && A[i - 1] > A[i]) continue;
            res = max(res, solve(i + 1, r, 0, rr) + V[i - l + 1]);
        }
    }

    // 删除右边
    if (rr == 0 || abs(A[r + 1] - A[r]) == 1) {
        for (int i = r - 1; i >= l; i--) {
            if (abs(A[i] - A[i + 1]) != 1) break;
            if (i < r - 1 && A[i + 1] > A[i] && A[i + 1] > A[i + 2]) continue;
            res = max(res, solve(l, i - 1, ll, 0) + V[r - i + 1]);
        }
    }

    return dp[l][r][ll][rr] = res;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &V[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    A[0] = A[N + 1] = -INF;
    memset(dp, -0x3f, sizeof(dp));
    printf("%d\n", solve(1, N, 0, 0));

    return 0;
}