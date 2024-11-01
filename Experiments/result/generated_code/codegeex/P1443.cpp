#include <stdio.h>
#include <queue>
using namespace std;

struct Point {
    int x, y;
};

int n, m, startX, startY;
int steps[400][400];
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void bfs() {
    queue<Point> q;
    q.push({startX, startY});
    steps[startX][startY] = 0;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && steps[nx][ny] == -1) {
                steps[nx][ny] = steps[current.x][current.y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &startX, &startY);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            steps[i][j] = -1;
        }
    }

    bfs();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%-5d", steps[i][j]);
        }
        printf("\n");
    }

    return 0;
}