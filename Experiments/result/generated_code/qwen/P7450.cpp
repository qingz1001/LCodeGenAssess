#include <stdio.h>
#include <stdlib.h>

#define MAXN 234
#define INF 1000000

int n, m, k;
int c[MAXN][MAXN];
int a[MAXN][MAXN];
int visited[MAXN][MAXN];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || c[x][y] == -1) return 0;
    visited[x][y] = 1;
    int count = 1;
    for (int i = 0; i < 4; i++) {
        count += dfs(x + dx[i], y + dy[i]);
    }
    return count;
}

void find_min_chunks() {
    int min_chunks = INF;
    int min_median = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && c[i][j] != -1) {
                memset(visited, 0, sizeof(visited));
                int size = dfs(i, j);
                if (size >= k) {
                    int values[size];
                    int index = 0;
                    for (int ii = 0; ii < n; ii++) {
                        for (int jj = 0; jj < m; jj++) {
                            if (visited[ii][jj]) {
                                values[index++] = a[ii][jj];
                            }
                        }
                    }
                    qsort(values, size, sizeof(int), (int (*)(const void *, const void *))strcmp);
                    int median = values[(size - 1) / 2];
                    if (size < min_chunks || (size == min_chunks && median < min_median)) {
                        min_chunks = size;
                        min_median = median;
                    }
                }
            }
        }
    }
    printf("%d %d\n", min_chunks == INF ? -1 : min_chunks, min_median == INF ? -1 : min_median);
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
        find_min_chunks();
    }
    return 0;
}