#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 233
#define MAX_M 233
#define INF 0x3f3f3f3f

int n, m, k;
int c[MAX_N][MAX_M];
int a[MAX_N][MAX_M];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int visited[MAX_N][MAX_M];
int types[MAX_N * MAX_M + 1];
int type_count;
int selected[MAX_N * MAX_M];
int selected_count;

bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && c[x][y] != -1;
}

void dfs(int x, int y) {
    visited[x][y] = 1;
    if (types[c[x][y]] == 0) type_count++;
    types[c[x][y]]++;
    selected[selected_count++] = a[x][y];
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (is_valid(nx, ny) && !visited[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void solve() {
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

    int min_count = INF, min_median = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (c[i][j] == -1) continue;
            memset(visited, 0, sizeof(visited));
            memset(types, 0, sizeof(types));
            selected_count = type_count = 0;
            dfs(i, j);

            if (type_count >= k && selected_count < min_count) {
                min_count = selected_count;
                qsort(selected, selected_count, sizeof(int), cmp);
                min_median = selected[(selected_count + 1) / 2 - 1];
            } else if (type_count >= k && selected_count == min_count) {
                qsort(selected, selected_count, sizeof(int), cmp);
                int median = selected[(selected_count + 1) / 2 - 1];
                if (median < min_median) {
                    min_median = median;
                }
            }
        }
    }

    if (min_count == INF) {
        printf("-1 -1\n");
    } else {
        printf("%d %d\n", min_count, min_median);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}