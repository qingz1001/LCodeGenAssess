#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 233
#define MAXK 5
#define INF 1000000000

int T, n, m, k;
int c[MAXN][MAXN], a[MAXN][MAXN];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

typedef struct {
    int x, y;
} Point;

typedef struct {
    int size, types;
    int values[MAXN * MAXN];
} Component;

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && c[x][y] != -1;
}

void bfs(int sx, int sy, Component *comp) {
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    int visited[MAXN][MAXN] = {0};
    int typeSet[MAXK + 1] = {0};

    queue[rear++] = (Point){sx, sy};
    visited[sx][sy] = 1;
    comp->values[comp->size++] = a[sx][sy];
    typeSet[c[sx][sy]] = 1;

    while (front < rear) {
        Point p = queue[front++];
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (isValid(nx, ny) && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                queue[rear++] = (Point){nx, ny};
                comp->values[comp->size++] = a[nx][ny];
                typeSet[c[nx][ny]] = 1;
            }
        }
    }

    for (int i = 1; i <= k; i++) {
        if (typeSet[i]) comp->types++;
    }
}

void solve() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &k);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &c[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }

        int minBlocks = INF, minMedian = INF;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (c[i][j] != -1) {
                    Component comp = {0, 0, {0}};
                    bfs(i, j, &comp);
                    if (comp.types >= k) {
                        qsort(comp.values, comp.size, sizeof(int), cmp);
                        int median = comp.values[(comp.size - 1) / 2];
                        if (comp.size < minBlocks || (comp.size == minBlocks && median < minMedian)) {
                            minBlocks = comp.size;
                            minMedian = median;
                        }
                    }
                }
            }
        }

        if (minBlocks == INF) {
            printf("-1 -1\n");
        } else {
            printf("%d %d\n", minBlocks, minMedian);
        }
    }
}

int main() {
    solve();
    return 0;
}