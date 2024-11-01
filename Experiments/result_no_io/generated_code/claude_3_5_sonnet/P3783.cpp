#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 50005
#define MAX_M 50005
#define MAX_K 20005
#define INF 0x3f3f3f3f

typedef long long ll;

struct Edge {
    int to, next, cost, dict;
} edge[MAX_M];

struct DictEdge {
    int to, next, ch;
} dict_edge[MAX_K];

int head[MAX_N], dict_head[MAX_K], cnt, dict_cnt;
int n, m, k;
int fail[MAX_K], len[MAX_K];
ll dist[MAX_N][MAX_K];

void add_edge(int u, int v, int cost, int dict) {
    edge[++cnt] = (struct Edge){v, head[u], cost, dict};
    head[u] = cnt;
}

void add_dict_edge(int u, int v, int ch) {
    dict_edge[++dict_cnt] = (struct DictEdge){v, dict_head[u], ch};
    dict_head[u] = dict_cnt;
}

void build_ac_automaton() {
    int q[MAX_K], front = 0, rear = 0;
    q[rear++] = 1;
    while (front < rear) {
        int u = q[front++];
        for (int i = dict_head[u]; i; i = dict_edge[i].next) {
            int v = dict_edge[i].to;
            int f = fail[u];
            while (f && !dict_edge[dict_head[f]].ch) f = fail[f];
            if (f) fail[v] = dict_edge[dict_head[f]].to;
            else fail[v] = 1;
            len[v] = len[fail[v]] + 1;
            q[rear++] = v;
        }
    }
}

void dijkstra() {
    static int vis[MAX_N][MAX_K];
    static ll d[MAX_N * MAX_K];
    static int id[MAX_N * MAX_K], tot;

    memset(dist, 0x3f, sizeof(dist));
    dist[1][1] = 0;
    d[++tot] = 0;
    id[tot] = 1 * MAX_K + 1;

    while (tot) {
        int x = id[1] / MAX_K, y = id[1] % MAX_K;
        d[1] = d[tot], id[1] = id[tot--];
        if (vis[x][y]) continue;
        vis[x][y] = 1;

        for (int i = head[x]; i; i = edge[i].next) {
            int v = edge[i].to, w = edge[i].cost, dict = edge[i].dict;
            int f = y;
            while (f && dict_edge[dict_head[f]].ch != dict) f = fail[f];
            if (f && dict_edge[dict_head[f]].ch == dict) f = dict_edge[dict_head[f]].to;
            else f = 1;

            if (dist[v][f] > dist[x][y] + w + len[dict] - len[f]) {
                dist[v][f] = dist[x][y] + w + len[dict] - len[f];
                d[++tot] = dist[v][f];
                id[tot] = v * MAX_K + f;
            }
        }

        while (tot > 1 && d[tot / 2] > d[tot]) {
            ll tmp = d[tot / 2];
            d[tot / 2] = d[tot];
            d[tot] = tmp;
            int tmp2 = id[tot / 2];
            id[tot / 2] = id[tot];
            id[tot] = tmp2;
            tot /= 2;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        
        memset(head, 0, sizeof(head));
        memset(dict_head, 0, sizeof(dict_head));
        cnt = dict_cnt = 0;

        for (int i = 1; i <= m; i++) {
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            add_edge(a, b, c, d);
        }

        for (int i = 1; i < k; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_dict_edge(u, v, w);
        }

        build_ac_automaton();
        dijkstra();

        for (int i = 2; i <= n; i++) {
            ll ans = INF;
            for (int j = 1; j <= k; j++) {
                ans = ans < dist[i][j] ? ans : dist[i][j];
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}