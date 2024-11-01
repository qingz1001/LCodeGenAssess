#include <stdio.h>
#include <limits.h>

#define MAX_N 20
#define INF INT_MAX

int n;
int dist[MAX_N + 1][MAX_N + 1];
int dp[1 << MAX_N][MAX_N];

int min(int a, int b) {
    return a < b ? a : b;
}

int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1) {
        return dist[pos][1];
    }
    
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }
    
    int ans = INF;
    for (int city = 1; city <= n; city++) {
        if ((mask & (1 << (city - 1))) == 0) {
            int newAns = dist[pos][city] + tsp(mask | (1 << (city - 1)), city);
            ans = min(ans, newAns);
        }
    }
    
    return dp[mask][pos] = ans;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    
    int result = tsp(1, 1);
    printf("%d\n", result);
    
    return 0;
}