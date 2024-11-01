#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000000000
#define MAX_M 100000

typedef long long ll;

typedef struct {
    int t, l, r, c;
} Plan;

int cmp(const void *a, const void *b) {
    return ((Plan*)a)->t - ((Plan*)b)->t;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    Plan plans[MAX_M];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &plans[i].t, &plans[i].l, &plans[i].r, &plans[i].c);
    }
    
    qsort(plans, m, sizeof(Plan), cmp);
    
    int dp[2][MAX_N + 2] = {0};
    int cur = 0, pre = 1;
    ll total_cost = 0;
    
    for (int i = 0; i < m; ) {
        int t = plans[i].t;
        memset(dp[cur], 0, sizeof(dp[cur]));
        
        while (i < m && plans[i].t == t) {
            int l = plans[i].l, r = plans[i].r, c = plans[i].c;
            for (int j = l; j <= r; j++) {
                dp[cur][j] = 1;
            }
            total_cost += c;
            i++;
        }
        
        for (int j = 1; j <= n; j++) {
            dp[cur][j] |= dp[pre][j-1] | dp[pre][j] | dp[pre][j+1];
        }
        
        cur ^= 1;
        pre ^= 1;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!dp[pre][i]) {
            printf("-1\n");
            return 0;
        }
    }
    
    printf("%lld\n", total_cost);
    
    return 0;
}