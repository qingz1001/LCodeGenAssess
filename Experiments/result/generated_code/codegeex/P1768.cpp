#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAXN 7000
#define MAXM 20000
#define INF LLONG_MAX

typedef long long ll;

struct Edge {
    int to, next;
    ll v, p;
} edges[MAXM + 5];

int head[MAXN + 5], edgeCount;
ll dist[MAXN + 5], distPrime[MAXN + 5];
bool inQueue[MAXN + 5];

void addEdge(int from, int to, ll v, ll p) {
    edges[++edgeCount] = {to, head[from], v, p};
    head[from] = edgeCount;
}

void SPFA(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(distPrime, 0x3f, sizeof(distPrime));
    memset(inQueue, false, sizeof(inQueue));
    dist[start] = distPrime[start] = 0;
    inQueue[start] = true;

    int queue[MAXN + 5], front = 0, rear = 0;
    queue[rear++] = start;

    while (front != rear) {
        int u = queue[front++];
        if (front == MAXN + 5) front = 0;
        inQueue[u] = false;

        for (int i = head[u]; i; i = edges[i].next) {
            int v = edges[i].to;
            ll vValue = edges[i].v;
            ll pValue = edges[i].p;

            if (dist[v] > dist[u] + vValue) {
                dist[v] = dist[u] + vValue;
                if (!inQueue[v]) {
                    inQueue[v] = true;
                    queue[rear++] = v;
                    if (rear == MAXN + 5) rear = 0;
                }
            }

            if (distPrime[v] > distPrime[u] + pValue) {
                distPrime[v] = distPrime[u] + pValue;
                if (!inQueue[v]) {
                    inQueue[v] = true;
                    queue[rear++] = v;
                    if (rear == MAXN + 5) rear = 0;
                }
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll vValue, pValue;
        scanf("%d %d %lld %lld", &u, &v, &vValue, &pValue);
        addEdge(u, v, vValue, pValue);
    }

    bool hasNegativeCycle = false;
    for (int i = 1; i <= n; ++i) {
        SPFA(i);
        if (dist[i] != distPrime[i]) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle) {
        printf("-1\n");
    } else {
        double maxRatio = 0.0;
        for (int i = 1; i <= n; ++i) {
            maxRatio = fmax(maxRatio, (double)dist[i] / distPrime[i]);
        }
        printf("%.1f\n", maxRatio);
    }

    return 0;
}