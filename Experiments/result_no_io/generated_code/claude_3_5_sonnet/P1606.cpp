#include <stdio.h>
#include <string.h>

#define MAX_M 30
#define MAX_N 30
#define INF 0x3f3f3f3f

int M, N;
int pond[MAX_M][MAX_N];
int dist[MAX_M][MAX_N];
long long ways[MAX_M][MAX_N];
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

void bfs(int sx, int sy) {
    int queue[MAX_M * MAX_N][2], front = 0, rear = 0;
    memset(dist, 0x3f, sizeof(dist));
    memset(ways, 0, sizeof(ways));
    
    dist[sx][sy] = 0;
    ways[sx][sy] = 1;
    queue[rear][0] = sx;
    queue[rear][1] = sy;
    rear++;
    
    while (front < rear) {
        int x = queue[front][0], y = queue[front][1];
        front++;
        
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N || pond[nx][ny] == 2) continue;
            
            if (pond[nx][ny] == 1 || pond[nx][ny] == 4) {
                if (dist[nx][ny] > dist[x][y]) {
                    dist[nx][ny] = dist[x][y];
                    ways[nx][ny] = ways[x][y];
                    queue[rear][0] = nx;
                    queue[rear][1] = ny;
                    rear++;
                } else if (dist[nx][ny] == dist[x][y]) {
                    ways[nx][ny] += ways[x][y];
                }
            } else {
                if (dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    ways[nx][ny] = ways[x][y];
                    queue[rear][0] = nx;
                    queue[rear][1] = ny;
                    rear++;
                } else if (dist[nx][ny] == dist[x][y] + 1) {
                    ways[nx][ny] += ways[x][y];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &M, &N);
    int sx, sy, ex, ey;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &pond[i][j]);
            if (pond[i][j] == 3) {
                sx = i;
                sy = j;
            } else if (pond[i][j] == 4) {
                ex = i;
                ey = j;
            }
        }
    }
    
    bfs(sx, sy);
    
    if (dist[ex][ey] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[ex][ey]);
        printf("%lld\n", ways[ex][ey]);
    }
    
    return 0;
}