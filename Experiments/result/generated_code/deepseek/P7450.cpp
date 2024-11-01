#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 233
#define MAXK 5

int T, n, m, k;
int c[MAXN][MAXN], a[MAXN][MAXN];
bool visited[MAXN][MAXN];

typedef struct {
    int x, y;
} Point;

typedef struct {
    int size;
    int types;
    int values[MAXN * MAXN];
} Component;

Component components[MAXN * MAXN];
int component_count;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void bfs(int x, int y) {
    Point queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = (Point){x, y};
    visited[x][y] = true;

    int type_count[MAXK + 1] = {0};
    int value_count = 0;
    int min_value = 1e6 + 1;

    while (front < rear) {
        Point p = queue[front++];
        components[component_count].values[value_count++] = a[p.x][p.y];
        if (a[p.x][p.y] < min_value) min_value = a[p.x][p.y];

        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && c[nx][ny] != -1) {
                visited[nx][ny] = true;
                queue[rear++] = (Point){nx, ny};
                type_count[c[nx][ny]]++;
            }
        }
    }

    int types = 0;
    for (int i = 1; i <= k; i++) {
        if (type_count[i] > 0) types++;
    }

    components[component_count].size = value_count;
    components[component_count].types = types;
    component_count++;
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
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

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
            }
        }

        component_count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (c[i][j] != -1 && !visited[i][j]) {
                    bfs(i, j);
                }
            }
        }

        int min_blocks = 1e6 + 1;
        int min_median = 1e6 + 1;
        bool found = false;

        for (int i = 0; i < component_count; i++) {
            if (components[i].types >= k) {
                found = true;
                if (components[i].size < min_blocks) {
                    min_blocks = components[i].size;
                    qsort(components[i].values, components[i].size, sizeof(int), cmp);
                    min_median = components[i].values[(components[i].size + 1) / 2 - 1];
                } else if (components[i].size == min_blocks) {
                    qsort(components[i].values, components[i].size, sizeof(int), cmp);
                    int median = components[i].values[(components[i].size + 1) / 2 - 1];
                    if (median < min_median) {
                        min_median = median;
                    }
                }
            }
        }

        if (found) {
            printf("%d %d\n", min_blocks, min_median);
        } else {
            printf("-1 -1\n");
        }
    }
    return 0;
}