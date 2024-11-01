#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_M 20
#define INF 0x3f3f3f3f

char map[MAX_N][MAX_M];
int dist[MAX_N][MAX_M];
int queue[MAX_N * MAX_M][2];
int front, rear;
int N, M, people_count;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void bfs() {
    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M && map[nx][ny] != 'X') {
                if (dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    queue[rear][0] = nx;
                    queue[rear][1] = ny;
                    rear++;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    memset(dist, 0x3f, sizeof(dist));
    front = rear = 0;
    people_count = 0;

    for (int i = 0; i < N; i++) {
        scanf("%s", map[i]);
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 'D') {
                dist[i][j] = 0;
                queue[rear][0] = i;
                queue[rear][1] = j;
                rear++;
            } else if (map[i][j] == '.') {
                people_count++;
            }
        }
    }

    bfs();

    int max_time = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == '.') {
                if (dist[i][j] == INF) {
                    printf("impossible\n");
                    return 0;
                }
                max_time = (max_time < dist[i][j]) ? dist[i][j] : max_time;
            }
        }
    }

    printf("%d\n", max_time + people_count);

    return 0;
}