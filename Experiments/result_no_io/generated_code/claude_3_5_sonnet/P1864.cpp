#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 70
#define INF 1e18

typedef long long ll;

int N, K;
int data[MAX_N], weight[MAX_N], freq[MAX_N];
int order[MAX_N];
ll dp[MAX_N][MAX_N];

int cmp(const void *a, const void *b) {
    return data[*(int*)a] - data[*(int*)b];
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

void solve() {
    for (int i = 0; i < N; i++) {
        order[i] = i;
    }
    qsort(order, N, sizeof(int), cmp);

    for (int len = 1; len <= N; len++) {
        for (int i = 0; i + len <= N; i++) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = INF;
            for (int k = i; k <= j; k++) {
                ll left = k > i ? dp[i][k-1] : 0;
                ll right = k < j ? dp[k+1][j] : 0;
                ll cost = 0;
                for (int t = i; t <= j; t++) {
                    cost += (ll)freq[order[t]] * (abs(t-k) + 1);
                }
                for (int t = i; t <= j; t++) {
                    if (t == k) continue;
                    if ((t < k && weight[order[t]] > weight[order[k]]) ||
                        (t > k && weight[order[t]] < weight[order[k]])) {
                        cost += K;
                    }
                }
                dp[i][j] = min(dp[i][j], left + right + cost);
            }
        }
    }

    printf("%lld\n", dp[0][N-1]);
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &data[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &weight[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &freq[i]);
    }

    solve();

    return 0;
}