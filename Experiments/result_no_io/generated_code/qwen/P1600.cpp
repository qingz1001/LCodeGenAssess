#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005

int n, m;
int tree[MAXN][2];
int w[MAXN];
int players[MAXN][2];
int result[MAXN];

void build_tree() {
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &tree[i][0], &tree[i][1]);
        tree[i][0]--;
        tree[i][1]--;
    }
}

void read_w() {
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
}

void read_players() {
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &players[i][0], &players[i][1]);
        players[i][0]--;
        players[i][1]--;
    }
}

void dfs(int u, int p, int time, int player_count) {
    if (time == w[u]) {
        result[u]++;
    }
    for (int i = 0; i < 2; i++) {
        int v = tree[u][i];
        if (v != p && v >= 0) {
            int new_time = time + 1;
            if (new_time <= w[v]) {
                dfs(v, u, new_time, player_count);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    build_tree();
    read_w();
    read_players();

    for (int i = 0; i < m; i++) {
        int start = players[i][0];
        int end = players[i][1];
        dfs(start, -1, 0, 1);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    return 0;
}