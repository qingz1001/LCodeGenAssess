#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int T, N, M, K, P;
int dist[MAXN], head[MAXN], next[MAXM], to[MAXM], val[MAXM], cnt;
int head2[MAXN], next2[MAXM], to2[MAXM], val2[MAXM], cnt2;
int dp[MAXN][55];
int inq[MAXN], que[MAXN], front, rear;

void add_edge(int u, int v, int w) {
    to[cnt] = v;
    val[cnt] = w;
    next[cnt] = head[u];
    head[u] = cnt++;
}

void add_edge2(int u, int v, int w) {
    to2[cnt2] = v;
    val2[cnt2] = w;
    next2[cnt2] = head2[u];
    head2[u] = cnt2++;
}

void spfa() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    inq[1] = 1;
    que[front = rear = 0] = 1;

    while (front <= rear) {
        int u = que[front++];
        inq[u] = 0;

        for (int i = head[u]; i != -1; i = next[i]) {
            int v = to[i];
            if (dist[v] > dist[u] + val[i]) {
                dist[v] = dist[u] + val[i];
                if (!inq[v]) {
                    que[++rear] = v;
                    inq[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d", &N, &M, &K, &P);
        cnt = cnt2 = 0;
        memset(head, -1, sizeof(head));
        memset(head2, -1, sizeof(head2));

        for (int i = 0; i < M; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add_edge(u, v, w);
            add_edge2(v, u, w);
        }

        spfa();

        if (dist[N] == 0x3f3f3f3f) {
            printf("-1\n");
            continue;
        }

        memset(dp, 0, sizeof(dp));
        dp[N][0] = 1;

        for (int u = 1; u <= N; u++) {
            for (int i = head[u]; i != -1; i = next[i]) {
                int v = to[i], w = val[i];
                if (dist[u] + w > dist[N] + K) continue;
                for (int j = 0; j <= K - (dist[u] + w - dist[N]); j++) {
                    dp[v][j] = (dp[v][j] + dp[u][j + (dist[u] + w - dist[N])]) % P;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i <= K; i++) {
            ans = (ans + dp[1][i]) % P;
        }

        if (ans == 0) {
            printf("-1\n");
        } else {
            printf("%d\n", ans);
        }
    }
    return 0;
}