#include <stdio.h>
#include <stdlib.h>

#define MAX 500
#define MAX_QUEUE 250000

int main(){
    int n, m, a, b;
    scanf("%d %d %d %d", &n, &m, &a, &b);
    
    // Initialize distance array
    int dist[MAX+1][MAX+1];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            dist[i][j] = -1;
        }
    }
    
    // Initialize BFS queue
    int *queue_x = (int*)malloc(sizeof(int)*MAX_QUEUE);
    int *queue_y = (int*)malloc(sizeof(int)*MAX_QUEUE);
    int head = 0, tail = 0;
    
    // Read infection sources
    for(int i=0;i<a;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        if(dist[x][y]==-1){
            dist[x][y] = 0;
            queue_x[tail] = x;
            queue_y[tail] = y;
            tail++;
        }
    }
    
    // Directions: up, down, left, right
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    
    // BFS
    while(head < tail){
        int cx = queue_x[head];
        int cy = queue_y[head];
        int current_dist = dist[cx][cy];
        for(int d=0;d<4;d++){
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if(nx >=1 && nx <=n && ny >=1 && ny <=m && dist[nx][ny]==-1){
                dist[nx][ny] = current_dist +1;
                queue_x[tail] = nx;
                queue_y[tail] = ny;
                tail++;
            }
        }
        head++;
    }
    
    // Read and answer lords' queries
    for(int i=0;i<b;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", dist[x][y]);
    }
    
    free(queue_x);
    free(queue_y);
    return 0;
}