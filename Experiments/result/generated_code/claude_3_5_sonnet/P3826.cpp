#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_P 100005

typedef long long ll;

struct Vegetable {
    ll a, s, c, x;
};

struct Vegetable veg[MAX_N];
ll dp[MAX_P][11];
ll sum[MAX_N][MAX_P];
int n, m, k;

int cmp(const void *a, const void *b) {
    return ((struct Vegetable*)b)->a - ((struct Vegetable*)a)->a;
}

void preprocess() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < MAX_P; j++) {
            if (veg[i].x == 0) {
                sum[i][j] = veg[i].c;
            } else {
                ll d = (veg[i].c + veg[i].x - 1) / veg[i].x;
                if (j < d) {
                    sum[i][j] = j * veg[i].x;
                } else {
                    sum[i][j] = veg[i].c;
                }
            }
        }
    }
}

ll solve(int p) {
    memset(dp, 0, sizeof(dp));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= p; j++) {
            for (int k = 0; k <= m && k <= sum[i][j]; k++) {
                ll profit = k * veg[i].a + (k > 0 ? veg[i].s : 0);
                if (j > 0) {
                    dp[j][k] = (dp[j][k] > dp[j-1][m-k] + profit) ? dp[j][k] : dp[j-1][m-k] + profit;
                } else {
                    dp[j][k] = (dp[j][k] > profit) ? dp[j][k] : profit;
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = (ans > dp[p][i]) ? ans : dp[p][i];
    }
    return ans;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld %lld %lld", &veg[i].a, &veg[i].s, &veg[i].c, &veg[i].x);
    }
    
    qsort(veg + 1, n, sizeof(struct Vegetable), cmp);
    preprocess();

    for (int i = 0; i < k; i++) {
        int p;
        scanf("%d", &p);
        printf("%lld\n", solve(p));
    }

    return 0;
}