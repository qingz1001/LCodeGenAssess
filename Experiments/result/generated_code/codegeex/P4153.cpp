#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
using namespace std;

const int N = 1.5e5 + 10, M = 3e5 + 10;
int n, m, s, t, k;
int head[N], nxt[M], ver[M], edge[M], tot;
long long dis[N];
bool vis[N];
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;

void add(int x, int y, int z) {
    nxt[++tot] = head[x];
    head[x] = tot;
    ver[tot] = y;
    edge[tot] = z;
}

void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push(make_pair(dis[s], s));
    while (!q.empty()) {
        int x = q.top().second;
        q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if (dis[y] > dis[x] + edge[i]) {
                dis[y] = dis[x] + edge[i];
                q.push(make_pair(dis[y], y));
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
    }
    dijkstra();
    if (dis[t] == 0x3f3f3f3f3f3f3f3f) {
        printf("-1\n");
        return 0;
    }
    long long ans = 0;
    for (int i = head[t]; i; i = nxt[i]) {
        int y = ver[i];
        if (dis[y] + edge[i] == dis[t]) {
            ans += edge[i];
            k--;
        }
    }
    printf("%lld\n", ans);
    while (k--) {
        if (k == 0) {
            printf("-1\n");
            return 0;
        }
        ans -= dis[t];
        for (int i = head[t]; i; i = nxt[i]) {
            int y = ver[i];
            if (dis[y] + edge[i] == dis[t]) {
                ans += edge[i];
                dis[t] = dis[y];
                break;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}