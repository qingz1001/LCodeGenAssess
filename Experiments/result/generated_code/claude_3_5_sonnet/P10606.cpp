#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200005

int n, m;
int a[MAX_N];
int dp[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        dp[y] = max(dp[y], x);
    }
    
    int last = 0, ans = 0;
    for (int i = n; i >= 1; i--) {
        last = max(last, dp[i]);
        if (last > i) {
            ans += a[i];
            last = 0;
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}