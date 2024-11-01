#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

#define MAXN 25
#define MAXM 25
#define MAXNODE 10005
#define INF 0x3f3f3f3f

int n, m;
int id[MAXN][MAXM]; // 矩阵的编号
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
char mp[MAXN][MAXM];
int cnt = 0;
int head[MAXNODE];
int dis[MAXNODE];
int pre[MAXNODE];
bool vis[MAXNODE];
int s, t;
int nodeNum = 0;

struct Edge {
    int to;
    int next;
    int cap;
} edge[MAXM * MAXM * 20];

void addEdge(int u, int v, int c) {
    edge[cnt].to = v;
    edge[cnt].cap = c;
    edge[cnt].next = head[u];
    head[u] = cnt++;
    
    edge[cnt].to = u;
    edge[cnt].cap = 0;
    edge[cnt].next = head[v];
    head[v] = cnt++;
}

void bfs() {
    queue<int> q;
    memset(dis, INF, sizeof(dis));
    memset(vis, false, sizeof(vis));
    q.push(s);
    dis[s] = 0;
    vis[s] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        for (int i = head[x]; i != -1; i = edge[i].next) {
            if (edge[i].cap > 0 && dis[edge[i].to] > dis[x] + 1) {
                dis[edge[i].to] = dis[x] + 1;
                pre[edge[i].to] = i;
                if (!vis[edge[i].to]) {
                    vis[edge[i].to] = true;
                    q.push(edge[i].to);
                }
            }
        }
    }
}

int dinic() {
    int maxflow = 0;
    while (true) {
        bfs();
        if (dis[t] == INF) {
            return maxflow;
        }
        int flow = INF;
        for (int i = t; i != s; i = edge[pre[i]^1].to) {
            flow = min(flow, edge[pre[i]].cap);
        }
        for (int i = t; i != s; i = edge[pre[i]^1].to) {
            edge[pre[i]].cap -= flow;
            edge[pre[i]^1].cap += flow;
        }
        maxflow += flow;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    s = 0;
    t = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%s", mp[i] + 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            id[i][j] = ++nodeNum;
            if (mp[i][j] == 'X') {
                continue;
            }
            if (mp[i][j] == '.') {
                addEdge(id[i][j], id[i][j] + n * m, INF);
            }
            if (mp[i][j] == 'D') {
                addEdge(id[i][j] + n * m, t, 1);
            }
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && mp[nx][ny] != 'X') {
                    addEdge(id[i][j] + n * m, id[nx][ny], 1);
                }
            }
        }
    }
    int ans = dinic();
    if (ans == nodeNum - 2) {
        printf("%d\n", dis[t] - 1);
    } else {
        printf("impossible\n");
    }
    return 0;
}