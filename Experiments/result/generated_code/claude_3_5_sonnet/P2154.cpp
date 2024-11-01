#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_W 100005
#define MAX_K 11
#define MOD 2147483648

typedef long long ll;

int N, M, W, k;
int x[MAX_W], y[MAX_W];
int cnt_x[MAX_W], cnt_y[MAX_W];
ll dp[MAX_K];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

ll count(int *arr, int len) {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    
    for (int i = 1; i < len; i++) {
        for (int j = k; j > 0; j--) {
            dp[j] = (dp[j] + dp[j-1] * (arr[i] - arr[i-1] - 1)) % MOD;
        }
    }
    
    return dp[k];
}

int main() {
    scanf("%d %d", &N, &M);
    scanf("%d", &W);
    
    for (int i = 0; i < W; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    
    scanf("%d", &k);
    
    qsort(x, W, sizeof(int), cmp);
    qsort(y, W, sizeof(int), cmp);
    
    int px = 0, py = 0;
    for (int i = 0; i <= N; i++) {
        while (px < W && x[px] == i) px++;
        cnt_x[i] = px;
    }
    for (int i = 0; i <= M; i++) {
        while (py < W && y[py] == i) py++;
        cnt_y[i] = py;
    }
    
    ll result = 0;
    for (int i = 0; i <= N; i++) {
        ll left = count(x, cnt_x[i]);
        ll right = count(x + cnt_x[i], W - cnt_x[i]);
        for (int j = 0; j <= M; j++) {
            ll down = count(y, cnt_y[j]);
            ll up = count(y + cnt_y[j], W - cnt_y[j]);
            result = (result + left * right * down * up) % MOD;
        }
    }
    
    printf("%lld\n", result);
    
    return 0;
}