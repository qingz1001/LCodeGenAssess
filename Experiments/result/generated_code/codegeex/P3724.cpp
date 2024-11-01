#include <stdio.h>
#include <string.h>
#include <algorithm>
#define ll long long
#define inf 1e9
using namespace std;

int n, m, mc;
int a[105], w[105];
ll C[25];

struct node {
    ll x, y;
    bool operator < (const node &A) const {
        return x == A.x ? y < A.y : x < A.x;
    }
} dp[105][105][105];

bool vis[105][105][105];

ll DFS(int day, int level, int attack, int limit) {
    if (day > n) return 0;
    if (vis[day][level][attack]) return dp[day][level][attack].y;
    vis[day][level][attack] = true;

    ll res = 0;
    // 不攻击大佬
    res = max(res, DFS(day + 1, level, attack, limit));
    // 攻击大佬
    if (attack < 2 && C[limit] - attack * level * level >= 0)
        res = max(res, 1 + DFS(day + 1, 0, 1, limit) + (C[limit] - attack * level * level) / (level * level));
    // 升级
    if (level < n) {
        ll new_level = level + 1;
        ll new_attack = attack * level;
        res = max(res, DFS(day + 1, new_level, new_attack, limit));
    }
    // 恢复自信
    if (mc - a[day] >= 0) {
        ll new_conf = min(mc, w[day] + mc - a[day]);
        res = max(res, DFS(day + 1, level, attack, new_conf));
    }
    dp[day][level][attack].x = day;
    dp[day][level][attack].y = res;
    return res;
}

int main() {
    scanf("%d%d%d", &n, &m, &mc);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    for (int i = 1; i <= m; i++) scanf("%lld", &C[i]);

    for (int i = 1; i <= m; i++) {
        memset(vis, 0, sizeof(vis));
        if (DFS(1, 0, 0, i) >= 0) printf("1\n");
        else printf("0\n");
    }

    return 0;
}