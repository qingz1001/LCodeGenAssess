#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20010
#define INF 0x3f3f3f3f

typedef struct Node {
    int v, c;
    struct Node *next;
} Node;

Node *head[MAXN];
int n, k, d[MAXN], c[MAXN], s[MAXN], w[MAXN], dp[MAXN][110];
int q[MAXN], l, r;

void addEdge(int u, int v, int c) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->v = v;
    newNode->c = c;
    newNode->next = head[u];
    head[u] = newNode;
}

void dijkstra(int start) {
    memset(dp, INF, sizeof(dp));
    dp[start][0] = 0;
    q[l = r = 1] = start;
    for (int i = 1; i <= n; i++) {
        int u = q[l];
        q[l++] = INF;
        for (Node *p = head[u]; p; p = p->next) {
            int v = p->v, c = p->c;
            for (int j = k; j > 0; j--) {
                if (dp[u][j] < INF) {
                    dp[v][j] = (dp[v][j] < dp[u][j] + c) ? dp[v][j] : dp[u][j] + c;
                    dp[v][j - 1] = (dp[v][j - 1] < dp[u][j - 1] + w[v]) ? dp[v][j - 1] : dp[u][j - 1] + w[v];
                    if (dp[v][j] < dp[v][j - 1]) {
                        q[++r] = v;
                    } else {
                        q[++r] = v;
                        int x = r;
                        while (x > l && dp[q[x]][j] > dp[q[x - 1]][j]) {
                            int temp = q[x];
                            q[x] = q[x - 1];
                            q[x - 1] = temp;
                            x--;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (d[j] - d[i] <= s[i]) {
                addEdge(i, j, c[i]);
            }
        }
    }

    dijkstra(1);

    int ans = INF;
    for (int i = 0; i <= k; i++) {
        ans = (ans < dp[1][i]) ? ans : dp[1][i];
    }

    printf("%d\n", ans);
    return 0;
}