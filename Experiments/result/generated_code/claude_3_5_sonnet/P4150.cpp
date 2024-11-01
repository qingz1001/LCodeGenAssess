#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 100005
#define MAX_M 6

int n, q;
int grid[MAX_M][MAX_N];
int dist[MAX_M][MAX_N];
int queue[MAX_M * MAX_N][2];
int head, tail;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void bfs(int sx, int sy) {
    for (int i = 0; i < MAX_M; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INT_MAX;
        }
    }
    
    head = tail = 0;
    queue[tail][0] = sx;
    queue[tail][1] = sy;
    tail++;
    dist[sx][sy] = grid[sx][sy];
    
    while (head < tail) {
        int x = queue[head][0];
        int y = queue[head][1];
        head++;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < MAX_M && ny >= 0 && ny < n) {
                int new_dist = dist[x][y] + grid[nx][ny];
                if (new_dist < dist[nx][ny]) {
                    dist[nx][ny] = new_dist;
                    queue[tail][0] = nx;
                    queue[tail][1] = ny;
                    tail++;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < MAX_M; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    scanf("%d", &q);
    
    while (q--) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            x--; y--;
            grid[x][y] = c;
        } else {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1--; y1--; x2--; y2--;
            bfs(x1, y1);
            printf("%d\n", dist[x2][y2]);
        }
    }
    
    return 0;
}