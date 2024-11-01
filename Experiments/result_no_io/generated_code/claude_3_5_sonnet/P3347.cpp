#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 101
#define MAX_M 101
#define INF 1e18

typedef long long ll;

int n, m;
int a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_M];
int graph[MAX_N][MAX_M];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

void mcmf(int s, int t, ll *flow, ll *cost) {
    static int pre[MAX_N + MAX_M + 2], id[MAX_N + MAX_M + 2];
    static ll dis[MAX_N + MAX_M + 2];
    static char inq[MAX_N + MAX_M + 2];
    int q[MAX_N + MAX_M + 2], head, tail;
    *flow = *cost = 0;
    while (1) {
        for (int i = s; i <= t; i++) dis[i] = INF;
        dis[s] = 0;
        head = tail = 0;
        q[tail++] = s;
        inq[s] = 1;
        while (head < tail) {
            int u = q[head++];
            inq[u] = 0;
            if (u <= n) {
                for (int v = n + 1; v <= n + m; v++) {
                    if (graph[u][v - n]) {
                        ll w = (ll)a[u] * (2 * (*flow + 1) - 1) + b[u];
                        if (dis[v] > dis[u] + w) {
                            dis[v] = dis[u] + w;
                            pre[v] = u;
                            id[v] = v - n;
                            if (!inq[v]) {
                                q[tail++] = v;
                                inq[v] = 1;
                            }
                        }
                    }
                }
            } else if (u <= n + m) {
                if (dis[t] > dis[u]) {
                    dis[t] = dis[u];
                    pre[t] = u;
                }
            } else {
                for (int v = 1; v <= n; v++) {
                    if (graph[v][u - n - m]) {
                        if (dis[v] > dis[u]) {
                            dis[v] = dis[u];
                            pre[v] = u;
                            id[v] = u - n - m;
                            if (!inq[v]) {
                                q[tail++] = v;
                                inq[v] = 1;
                            }
                        }
                    }
                }
            }
        }
        if (dis[t] == INF) break;
        ll f = INF;
        for (int u = t; u != s; u = pre[u]) {
            if (pre[u] <= n)
                f = f < c[pre[u]] - (*flow) ? f : c[pre[u]] - (*flow);
            else if (u <= n + m)
                f = f < d[u - n] ? f : d[u - n];
        }
        *flow += f;
        *cost += f * dis[t];
        for (int u = t; u != s; u = pre[u]) {
            if (pre[u] <= n) {
                graph[pre[u]][id[u]]--;
                graph[id[u] + n + m][pre[u]]++;
            } else if (u <= n + m) {
                d[u - n] -= f;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    int s = 0, t = n + m + 1;
    for (int i = 1; i <= n; i++) {
        graph[s][i] = c[i];
    }
    for (int i = 1; i <= m; i++) {
        graph[n + i][t] = d[i];
    }
    
    ll flow, cost;
    mcmf(s, t, &flow, &cost);
    
    printf("%lld\n", flow);
    
    if (cost == 0) {
        printf("0/1\n");
    } else {
        ll g = gcd(cost, flow);
        printf("%lld/%lld\n", cost / g, flow / g);
    }
    
    return 0;
}