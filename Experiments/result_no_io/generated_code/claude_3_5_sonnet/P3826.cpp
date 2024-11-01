#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 11
#define MAX_P 100005

typedef long long ll;

struct Vegetable {
    ll a, s, c, x;
};

struct Vegetable vegs[MAX_N];
ll dp[MAX_P][MAX_M];
ll remain[MAX_N][MAX_P];
int n, m, k;

int cmp(const void *a, const void *b) {
    return ((struct Vegetable *)b)->a - ((struct Vegetable *)a)->a;
}

void init_remain() {
    for (int i = 0; i < n; i++) {
        ll c = vegs[i].c, x = vegs[i].x;
        for (int j = 1; j < MAX_P; j++) {
            if (x == 0) {
                remain[i][j] = c;
            } else {
                remain[i][j] = (c > x * j) ? (c - x * j) : 0;
            }
        }
    }
}

ll solve(int p) {
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < n; i++) {
        for (int j = p; j > 0; j--) {
            for (int k = 0; k < m; k++) {
                ll cnt = remain[i][j-1] - remain[i][j];
                if (k + cnt > m) cnt = m - k;
                if (cnt <= 0) continue;
                
                ll add = cnt * vegs[i].a;
                if (dp[j-1][k] == 0 && j > 1) continue;
                
                if (dp[j-1][k] > 0 || j == 1) {
                    if (dp[j][k+cnt] < dp[j-1][k] + add) {
                        dp[j][k+cnt] = dp[j-1][k] + add;
                    }
                }
            }
        }
    }
    
    ll res = 0;
    for (int i = 0; i <= m; i++) {
        if (dp[p][i] > res) res = dp[p][i];
    }
    
    for (int i = 0; i < n; i++) {
        if (remain[i][p] < vegs[i].c) {
            res += vegs[i].s;
        }
    }
    
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld%lld%lld", &vegs[i].a, &vegs[i].s, &vegs[i].c, &vegs[i].x);
    }
    
    qsort(vegs, n, sizeof(struct Vegetable), cmp);
    init_remain();
    
    for (int i = 0; i < k; i++) {
        int p;
        scanf("%d", &p);
        printf("%lld\n", solve(p));
    }
    
    return 0;
}