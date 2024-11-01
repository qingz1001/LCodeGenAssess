#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_M 50
#define INF 1000000

typedef struct {
    int x, y;
    char dir;
} State;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
char directions[] = {'W', 'E', 'N', 'S'};

int is_valid(int n, int m, int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int get_direction_index(char dir) {
    for (int i = 0; i < 4; i++) {
        if (directions[i] == dir) return i;
    }
    return -1;
}

int min_time_to_reach_goal(int n, int m, int grid[MAX_N][MAX_M], State start, State goal) {
    int dist[MAX_N][MAX_M][4];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                dist[i][j][k] = INF;
            }
        }
    }

    dist[start.x][start.y][get_direction_index(start.dir)] = 0;

    typedef struct {
        int x, y, dir, steps;
    } Node;

    Node queue[n * m * 4];
    int front = 0, rear = 0;

    queue[rear++] = (Node){start.x, start.y, get_direction_index(start.dir), 0};

    while (front != rear) {
        Node current = queue[front++];

        int cx = current.x, cy = current.y, cdir = current.dir, csteps = current.steps;

        if (cx == goal.x && cy == goal.y) {
            return csteps;
        }

        // Move forward
        for (int step = 1; step <= 3; step++) {
            int nx = cx + dx[cdir] * step, ny = cy + dy[cdir] * step;
            if (!is_valid(n, m, nx, ny) || grid[nx][ny] == 1) break;
            if (dist[nx][ny][cdir] > csteps + step) {
                dist[nx][ny][cdir] = csteps + step;
                queue[rear++] = (Node){nx, ny, cdir, csteps + step};
            }
        }

        // Turn left and right
        for (int d = 0; d < 2; d++) {
            int new_dir = (cdir + (d ? 1 : -1) + 4) % 4;
            if (dist[cx][cy][new_dir] > csteps + 1) {
                dist[cx][cy][new_dir] = csteps + 1;
                queue[rear++] = (Node){cx, cy, new_dir, csteps + 1};
            }
        }
    }

    return -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int grid[MAX_N][MAX_M];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    State start, goal;
    scanf("%d %d %d %d %c", &start.x, &start.y, &goal.x, &goal.y, &start.dir);

    printf("%d\n", min_time_to_reach_goal(n, m, grid, start, goal));

    return 0;
}