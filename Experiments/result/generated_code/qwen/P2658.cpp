#include <stdio.h>
#include <stdlib.h>

#define MAXN 500
#define INF 1e9

int M, N;
int height[MAXN][MAXN];
int is_marker[MAXN][MAXN];

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void bfs(int start_x, int start_y, int D) {
    int queue[MAXN * MAXN][2];
    int front = 0, rear = 0;
    queue[rear][0] = start_x;
    queue[rear++][1] = start_y;
    is_marker[start_x][start_y] = 0;

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front++][1];

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N && abs(height[nx][ny] - height[x][y]) <= D && is_marker[nx][ny]) {
                queue[rear][0] = nx;
                queue[rear++][1] = ny;
                is_marker[nx][ny] = 0;
            }
        }
    }
}

int find_min_difficulty() {
    int min_D = 0;
    int max_D = INF;

    while (min_D < max_D) {
        int mid_D = (min_D + max_D) / 2;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                is_marker[i][j] = 0;
            }
        }

        int markers_count = 0;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (is_marker[i][j]) {
                    bfs(i, j, mid_D);
                    markers_count++;
                }
            }
        }

        if (markers_count == 1) {
            max_D = mid_D;
        } else if (markers_count > 1) {
            min_D = mid_D + 1;
        } else {
            return mid_D;
        }
    }

    return min_D;
}

int main() {
    scanf("%d %d", &M, &N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &height[i][j]);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &is_marker[i][j]);
        }
    }

    printf("%d\n", find_min_difficulty());

    return 0;
}