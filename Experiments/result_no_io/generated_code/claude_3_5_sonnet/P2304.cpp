#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 100005
#define INF 1e18

typedef long long ll;

struct Point {
    ll x, y;
} trees[MAXN];

int n, m;
int vis[MAXN], path[MAXN];
int graph[MAXN][MAXN];

int cmp(const void *a, const void *b) {
    struct Point *pa = (struct Point *)a;
    struct Point *pb = (struct Point *)b;
    if (pa->x != pb->x) return pa->x - pb->x;
    return pa->y - pb->y;
}

ll dist(struct Point a, struct Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int check_direction(struct Point from, struct Point to) {
    if (to.x == from.x && to.y > from.y) return 1; // up
    if (to.x > from.x && to.y == from.y) return 2; // right
    if (to.x < from.x && to.y == from.y) return 3; // left
    if (to.x > from.x && to.y > from.y && to.x - from.x == to.y - from.y) return 4; // right-up
    if (to.x < from.x && to.y > from.y && from.x - to.x == to.y - from.y) return 5; // left-up
    return 0;
}

void dfs(int cur, int depth) {
    if (depth > m) {
        m = depth;
        memcpy(path, vis, sizeof(vis));
    }
    
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int dir = check_direction(trees[cur], trees[i]);
            if (dir) {
                int valid = 1;
                for (int j = 1; j <= n; j++) {
                    if (!vis[j] && j != i && check_direction(trees[cur], trees[j]) == dir) {
                        if (dist(trees[cur], trees[j]) < dist(trees[cur], trees[i])) {
                            valid = 0;
                            break;
                        }
                    }
                }
                if (valid) {
                    vis[i] = 1;
                    dfs(i, depth + 1);
                    vis[i] = 0;
                }
            }
        }
    }
}

int dfs2(int cur) {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (graph[cur][i] && !vis[i]) {
            vis[i] = 1;
            res = fmax(res, dfs2(i) + 1);
            vis[i] = 0;
        }
    }
    return res;
}

int main() {
    scanf("%d", &n);
    trees[0].x = trees[0].y = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &trees[i].x, &trees[i].y);
    }
    
    qsort(trees + 1, n, sizeof(struct Point), cmp);
    
    dfs(0, 0);
    
    printf("%d\n", m);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (path[j] == i) {
                printf("%d ", j);
                break;
            }
        }
    }
    printf("\n");
    
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int dir = check_direction(trees[i], trees[j]);
            if (dir == 1 || dir == 4 || dir == 5) {
                graph[i][j] = graph[j][i] = 1;
            }
        }
    }
    
    int ans = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            ans += dfs2(i) + 1;
        }
    }
    
    printf("%d\n", ans);
    
    return 0;
}