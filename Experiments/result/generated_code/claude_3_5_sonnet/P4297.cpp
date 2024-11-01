#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_M (1<<MAX_N)
#define INF 0x3f3f3f3f3f3f3f3fLL

typedef long long ll;

int N, M;
int init[MAX_M], C[MAX_M];
ll F[MAX_M][MAX_M];
ll dp[MAX_M][2];

ll min(ll a, ll b) {
    return a < b ? a : b;
}

void solve(int l, int r) {
    if (l == r) {
        dp[l][init[l]] = 0;
        dp[l][1-init[l]] = C[l];
        return;
    }
    
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid+1, r);
    
    int len = r - l + 1;
    ll cost[2][2] = {{0}};
    
    for (int i = l; i <= mid; i++) {
        for (int j = mid+1; j <= r; j++) {
            cost[0][0] += F[i][j];
            cost[0][1] += F[i][j] * 3;
            cost[1][0] += F[i][j] * 3;
            cost[1][1] += F[i][j] * 5;
        }
    }
    
    for (int s = 0; s < 2; s++) {
        for (int t = 0; t < 2; t++) {
            ll sum = 0;
            for (int i = l; i <= mid; i++) {
                sum += dp[i][s];
            }
            for (int i = mid+1; i <= r; i++) {
                sum += dp[i][t];
            }
            sum += cost[s][t];
            dp[l][s] = min(dp[l][s], sum);
        }
    }
}

int main() {
    scanf("%d", &N);
    M = 1 << N;
    
    for (int i = 0; i < M; i++) {
        scanf("%d", &init[i]);
    }
    
    for (int i = 0; i < M; i++) {
        scanf("%d", &C[i]);
    }
    
    for (int i = 0; i < M-1; i++) {
        for (int j = i+1; j < M; j++) {
            scanf("%lld", &F[i][j]);
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    solve(0, M-1);
    
    printf("%lld\n", min(dp[0][0], dp[0][1]));
    
    return 0;
}