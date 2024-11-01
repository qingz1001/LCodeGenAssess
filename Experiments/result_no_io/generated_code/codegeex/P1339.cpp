#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 2501
#define MAXM 6201

int n, m, s, t;
int u[MAXM], v[MAXM], w[MAXM];
int dist[MAXN];
bool inq[MAXN];

void spfa() {
    memset(inq, false, sizeof(inq));
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[s] = 0;
    inq[s] = true;
    int que[MAXN], head = 0, tail = 0;
    que[tail++] = s;

    while (head != tail) {
        int x = que[head++];
        head %= MAXN;
        inq[x] = false;
        for (int i = 0; i < m; i++) {
            if (u[i] == x && dist[v[i]] > dist[x] + w[i]) {
                dist[v[i]] = dist[x] + w[i];
                if (!inq[v[i]]) {
                    que[tail++] = v[i];
                    tail %= MAXN;
                    inq[v[i]] = true;
                }
            }
            if (v[i] == x && dist[u[i]] > dist[x] + w[i]) {
                dist[u[i]] = dist[x] + w[i];
                if (!inq[u[i]]) {
                    que[tail++] = u[i];
                    tail %= MAXN;
                    inq[u[i]] = true;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &w[i]);
    }
    spfa();
    printf("%d\n", dist[t]);
    return 0;
}