#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 71
#define INF 1e18

typedef long long ll;

int N, K;
int data[MAXN], weight[MAXN], freq[MAXN];
ll dp[MAXN][MAXN][MAXN];
int root[MAXN][MAXN];

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

void solve() {
    int order[MAXN];
    for (int i = 1; i <= N; i++) order[i] = i;
    qsort(order + 1, N, sizeof(int), cmp);

    for (int len = 1; len <= N; len++) {
        for (int l = 1; l + len - 1 <= N; l++) {
            int r = l + len - 1;
            dp[l][r][order[r]] = INF;
            for (int k = l; k <= r; k++) {
                ll sum = 0;
                for (int i = l; i <= r; i++) sum += freq[order[i]];
                
                ll left = k > l ? dp[l][k-1][order[k-1]] : 0;
                ll right = k < r ? dp[k+1][r][order[r]] : 0;
                ll cost = sum + left + right;

                if (cost < dp[l][r][order[r]]) {
                    dp[l][r][order[r]] = cost;
                    root[l][r] = k;
                }
            }

            for (int i = r-1; i >= l; i--) {
                dp[l][r][order[i]] = dp[l][r][order[i+1]];
                if (weight[order[i]] > weight[order[i+1]])
                    dp[l][r][order[i]] = dp[l][r][order[i+1]] + K;
            }
        }
    }

    printf("%lld\n", dp[1][N][order[1]]);
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 1; i <= N; i++) scanf("%d", &data[i]);
    for (int i = 1; i <= N; i++) scanf("%d", &weight[i]);
    for (int i = 1; i <= N; i++) scanf("%d", &freq[i]);

    solve();

    return 0;
}