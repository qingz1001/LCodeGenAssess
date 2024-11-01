#include <stdio.h>
#include <queue>
using namespace std;

struct Position {
    int x, y;
};

int n, m, a, b;
int grid[501][501];
int time_grid[501][501];

void bfs(int startX, int startY) {
    queue<Position> q;
    q.push({startX, startY});
    time_grid[startX][startY] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && time_grid[nx][ny] == -1) {
                time_grid[nx][ny] = time_grid[current.x][current.y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);

    for (int i = 0; i < a; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        grid[x][y] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == 1) {
                bfs(i, j);
            }
        }
    }

    for (int i = 0; i < b; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", time_grid[x][y]);
    }

    return 0;
}