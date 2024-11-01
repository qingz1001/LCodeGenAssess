#include <stdio.h>
#include <string.h>

#define MAXN 505
#define INF 0x3f3f3f3f

int n;
int a[MAXN][MAXN];
int dp[1<<20];
int pre[1<<20];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int s) {
    if (dp[s] != -1) return dp[s];
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (s & (1<<i)) cnt++;
    if (cnt == n) return dp[s] = 0;
    
    if (cnt % 2 == 0) {
        dp[s] = -INF;
        for (int i = 0; i < n; i++) {
            if (!(s & (1<<i))) {
                int t = dfs(s | (1<<i));
                if (t > dp[s]) {
                    dp[s] = t;
                    pre[s] = i;
                }
            }
        }
    } else {
        dp[s] = INF;
        int max_pair = -1, max_val = -1;
        for (int i = 0; i < n; i++) {
            if (s & (1<<i)) {
                for (int j = 0; j < n; j++) {
                    if (!(s & (1<<j))) {
                        if (a[i][j] > max_val) {
                            max_val = a[i][j];
                            max_pair = j;
                        }
                    }
                }
            }
        }
        dp[s] = dfs(s | (1<<max_pair));
        pre[s] = max_pair;
    }
    return dp[s];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            scanf("%d", &a[i][j]);
            a[j][i] = a[i][j];
        }
    }
    
    memset(dp, -1, sizeof(dp));
    int res = dfs(0);
    
    if (res <= 0) {
        printf("0\n");
    } else {
        printf("1\n%d\n", res);
    }
    
    return 0;
}