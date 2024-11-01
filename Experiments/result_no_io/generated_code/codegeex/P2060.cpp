#include <stdio.h>
#include <queue>
#include <limits.h>

using namespace std;

struct Node {
    int x, y, step;
};

int dx[8] = {1, 2, 1, 2, -1, -2, -1, -2};
int dy[8] = {2, 1, -2, -1, 2, 1, -2, -1};
int visited[10000001][10000001];
int x_s, y_s;

int bfs(int x_p, int y_p) {
    queue<Node> q;
    q.push({x_p, y_p, 0});
    visited[x_p][y_p] = 1;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.x == x_s && current.y == y_s) {
            return current.step;
        }

        for (int i = 0; i < 8; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && ny >= 0 && visited[nx][ny] == 0) {
                visited[nx][ny] = 1;
                q.push({nx, ny, current.step + 1});
            }
        }
    }

    return -1; // Should not reach here if input is valid
}

int main() {
    int x_p, y_p;
    scanf("%d%d%d%d", &x_p, &y_p, &x_s, &y_s);

    printf("%d\n", bfs(x_p, y_p));

    return 0;
}