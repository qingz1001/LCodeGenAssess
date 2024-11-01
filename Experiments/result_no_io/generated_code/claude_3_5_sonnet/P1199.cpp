#include <stdio.h>
#include <string.h>

#define MAXN 505
#define INF 0x3f3f3f3f

int n;
int intimacy[MAXN][MAXN];
int dp[1 << 20];
int path[1 << 20];

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int state) {
    if (dp[state] != -1) return dp[state];
    if (__builtin_popcount(state) == n) return 0;
    
    int player = __builtin_popcount(state) % 2;
    int res = player ? INF : -INF;
    int choose = -1;
    
    for (int i = 0; i < n; i++) {
        if (state & (1 << i)) continue;
        int nxt = state | (1 << i);
        int val;
        
        if (player == 0) {
            val = dfs(nxt);
            if (val > res) {
                res = val;
                choose = i;
            }
        } else {
            int maxIntimacy = -INF;
            for (int j = 0; j < n; j++) {
                if (!(state & (1 << j))) continue;
                maxIntimacy = max(maxIntimacy, intimacy[i][j]);
            }
            val = max(maxIntimacy, dfs(nxt));
            if (val < res) {
                res = val;
                choose = i;
            }
        }
    }
    
    path[state] = choose;
    return dp[state] = res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &intimacy[i][j]);
            intimacy[j][i] = intimacy[i][j];
        }
    }
    
    memset(dp, -1, sizeof(dp));
    int result = dfs(0);
    
    if (result <= 0) {
        printf("0\n");
    } else {
        printf("1\n%d\n", result);
    }
    
    return 0;
}