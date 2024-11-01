#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005
#define MAXD 2000
#define INF 0x3f3f3f3f

int n, d, k;
int x[MAXN], s[MAXN];
int dp[MAXD];

void update(int dist, int score) {
    for (int i = dist; i >= 0; --i) {
        if (dp[i] + score > dp[(dist - i + d) % d]) {
            dp[(dist - i + d) % d] = dp[i] + score;
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &d, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x[i], &s[i]);
    }

    for (int i = 0; i < d; ++i) {
        dp[i] = -INF;
    }
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        update(x[i] % d, s[i]);
    }

    int min_cost = INF;
    for (int i = 0; i < d; ++i) {
        if (dp[i] >= k) {
            min_cost = 0;
            break;
        } else {
            int cost = d - i;
            if (cost >= 1 && cost <= d) {
                min_cost = cost;
            }
        }
    }

    printf("%d\n", min_cost == INF ? -1 : min_cost);

    return 0;
}