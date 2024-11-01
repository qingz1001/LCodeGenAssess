#include <stdio.h>
#include <string.h>

#define MAX_N 201
#define MAX_M 201

char front[MAX_N][MAX_M];
char back[MAX_N][MAX_M];
int n, m;
int visited[MAX_N][MAX_M];

int dx[] = {-1, -1, 1, 1};
int dy[] = {-1, 1, -1, 1};

int dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) return 0;
    if (visited[x][y]) return 0;
    if (front[x][y] == '.' && back[x][y] == '.') return 0;

    visited[x][y] = 1;
    int count = 1;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if ((front[x][y] == '/' || front[x][y] == 'X') && (i == 1 || i == 2)) {
            count += dfs(nx, ny);
        }
        if ((front[x][y] == '\\' || front[x][y] == 'X') && (i == 0 || i == 3)) {
            count += dfs(nx, ny);
        }
        if ((back[x][y] == '/' || back[x][y] == 'X') && (i == 1 || i == 2)) {
            count += dfs(nx, ny);
        }
        if ((back[x][y] == '\\' || back[x][y] == 'X') && (i == 0 || i == 3)) {
            count += dfs(nx, ny);
        }
    }

    return count;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%s", front[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", back[i]);
    }

    int needles = 0;
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && (front[i][j] != '.' || back[i][j] != '.')) {
                dfs(i, j);
                needles++;
            }
        }
    }

    printf("%d\n", needles);

    return 0;
}