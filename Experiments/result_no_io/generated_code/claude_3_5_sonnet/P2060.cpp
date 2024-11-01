#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 210
#define INF 0x3f3f3f3f

int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

int dist[MAX_N][MAX_N];
int queue[MAX_N * MAX_N][2];

int bfs(int sx, int sy, int ex, int ey) {
    memset(dist, 0x3f, sizeof(dist));
    int head = 0, tail = 0;
    
    queue[tail][0] = sx;
    queue[tail][1] = sy;
    tail++;
    dist[sx][sy] = 0;
    
    while (head < tail) {
        int x = queue[head][0];
        int y = queue[head][1];
        head++;
        
        if (x == ex && y == ey) {
            return dist[x][y];
        }
        
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < MAX_N && ny >= 0 && ny < MAX_N && dist[nx][ny] == INF) {
                dist[nx][ny] = dist[x][y] + 1;
                queue[tail][0] = nx;
                queue[tail][1] = ny;
                tail++;
            }
        }
    }
    
    return -1;
}

int main() {
    int xp, yp, xs, ys;
    scanf("%d %d %d %d", &xp, &yp, &xs, &ys);
    
    int dx = abs(xs - xp);
    int dy = abs(ys - yp);
    
    if (dx == 0 && dy == 0) {
        printf("0\n");
    } else if ((dx + dy) % 2 == 0) {
        if (dx == dy && dx % 2 == 0) {
            printf("%d\n", dx / 2);
        } else {
            printf("%d\n", bfs(0, 0, dx, dy));
        }
    } else {
        printf("-1\n");
    }
    
    return 0;
}