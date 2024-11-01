#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 35
#define MAXK 6
#define MAXH 6
#define MAXSTATES (1 << MAXK)
#define MAXNODE (MAXN * MAXN * MAXSTATES * MAXH)

struct Node {
    int x, y, state, health, next;
};

struct Edge {
    int to, state, health, next;
};

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int head[MAXNODE], edgeCount;
Node node[MAXNODE];
Edge edge[MAXNODE * 4];

void addNode(int x, int y, int state, int health) {
    int index = x * MAXN * MAXSTATES * MAXH + y * MAXSTATES * MAXH + state * MAXH + health;
    node[index].next = head[index];
    head[index] = edgeCount;
    edge[edgeCount].to = index;
    edge[edgeCount].state = state;
    edge[edgeCount].health = health;
    edge[edgeCount].next = -1;
    edgeCount++;
}

void addEdge(int from, int to, int state, int health) {
    edge[edgeCount].to = to;
    edge[edgeCount].state = state;
    edge[edgeCount].health = health;
    edge[edgeCount].next = head[from];
    head[from] = edgeCount;
    edgeCount++;
}

double dp[MAXNODE];

void dfs(int x, int y, int state, int health, int m, int n, int k, int H, int *p, char *map) {
    int index = x * MAXN * MAXSTATES * MAXH + y * MAXSTATES * MAXH + state * MAXH + health;
    if (dp[index] >= 0) return;
    dp[index] = 0;
    if (map[x * n + y] == '#') return;
    if (map[x * n + y] == '$' || map[x * n + y] == '@') {
        dp[index] = 1;
        return;
    }
    if (map[x * n + y] != '.') {
        int trapState = state & (1 << (map[x * n + y] - 'A'));
        double prob = (double)p[state] / p[state ^ trapState];
        if (trapState) {
            if (health > 1) {
                dfs(x, y, state ^ trapState, health - 1, m, n, k, H, p, map);
                dp[index] += dp[x * MAXN * MAXSTATES * MAXH + y * MAXSTATES * MAXH + (state ^ trapState) * MAXH + health - 1] * prob;
            }
        } else {
            dfs(x, y, state ^ trapState, health, m, n, k, H, p, map);
            dp[index] += dp[x * MAXN * MAXSTATES * MAXH + y * MAXSTATES * MAXH + (state ^ trapState) * MAXH + health] * prob;
        }
    } else {
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                dfs(nx, ny, state, health, m, n, k, H, p, map);
                dp[index] += dp[nx * MAXN * MAXSTATES * MAXH + ny * MAXSTATES * MAXH + state * MAXH + health];
            }
        }
    }
}

int main() {
    int m, n, k, H;
    scanf("%d%d%d%d", &m, &n, &k, &H);
    char map[MAXN * MAXN];
    for (int i = 0; i < m; i++) {
        scanf("%s", map + i * n);
    }
    int p[MAXSTATES];
    for (int i = 0; i < (1 << k); i++) {
        scanf("%d", p + i);
    }

    memset(dp, -1, sizeof(dp));
    dfs(0, 0, 0, H, m, n, k, H, p, map);

    printf("%.3f\n", dp[0 * MAXN * MAXSTATES * MAXH + 0 * MAXSTATES * MAXH + 0 * MAXH + H]);

    return 0;
}