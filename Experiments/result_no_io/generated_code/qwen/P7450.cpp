#include <stdio.h>
#include <stdlib.h>

#define MAXN 234
#define INF 1e9

int n, m, k;
int c[MAXN][MAXN], a[MAXN][MAXN];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

typedef struct {
    int x, y;
} Point;

void bfs(int x, int y) {
    if (c[x][y] == -1 || visited[x][y]) return;
    visited[x][y] = 1;
    queue[rear++] = (Point){x, y};
    while (front != rear) {
        Point p = queue[front++];
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && c[nx][ny] != -1) {
                visited[nx][ny] = 1;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }
}

int main() {
    int T;
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

        // Find all connected components
        int component_count = 0;
        int component_size[MAXN * MAXN];
        int component_id[MAXN][MAXN];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && c[i][j] != -1) {
                    component_size[component_count] = 0;
                    bfs(i, j);
                    component_id[i][j] = component_count;
                    component_count++;
                }
            }
        }

        // Check if there are enough distinct components
        if (component_count < k) {
            printf("-1 -1\n");
            continue;
        }

        // Calculate the minimum number of blocks and the smallest median value
        int min_blocks = INF;
        int min_median = INF;
        for (int size = k; size <= n * m; size++) {
            int count[component_count];
            for (int i = 0; i < component_count; i++) {
                count[i] = 0;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (c[i][j] != -1) {
                        count[component_id[i][j]]++;
                    }
                }
            }
            int valid = 1;
            for (int i = 0; i < component_count; i++) {
                if (count[i] > 0 && count[i] < k) {
                    valid = 0;
                    break;
                }
            }
            if (!valid) continue;

            // Sort the values in each component
            int values[size];
            int index = 0;
            for (int i = 0; i < component_count; i++) {
                if (count[i] > 0) {
                    for (int j = 0; j < n; j++) {
                        for (int l = 0; l < m; l++) {
                            if (component_id[j][l] == i && c[j][l] != -1) {
                                values[index++] = a[j][l];
                            }
                        }
                    }
                }
            }

            // Calculate the median
            qsort(values, size, sizeof(int), (int (*)(const void *, const void *))compare);
            int median = values[(size - 1) / 2];

            // Update the result if this is a better solution
            if (size < min_blocks || (size == min_blocks && median < min_median)) {
                min_blocks = size;
                min_median = median;
            }
        }

        printf("%d %d\n", min_blocks, min_median);
    }
    return 0;
}