#include <stdio.h>
#include <queue>
using namespace std;

int n, m, x, y;
int board[400][400];
int dir[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

struct Point {
    int x, y;
};

int isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int minSteps() {
    queue<Point> q;
    Point start = {x - 1, y - 1};
    q.push(start);
    board[start.x][start.y] = 0;

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int nx = current.x + dir[i][0];
            int ny = current.y + dir[i][1];

            if (isValid(nx, ny) && board[nx][ny] == -1) {
                board[nx][ny] = board[current.x][current.y] + 1;
                Point next = {nx, ny};
                q.push(next);
            }
        }
    }

    return board[x - 1][y - 1];
}

int main() {
    scanf("%d%d%d%d", &n, &m, &x, &y);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            board[i][j] = -1;
        }
    }

    int result = minSteps();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}