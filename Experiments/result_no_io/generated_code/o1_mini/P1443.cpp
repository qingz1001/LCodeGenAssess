#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

int main(){
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    x -= 1;
    y -= 1;
    
    int **dist = (int **)malloc(n * sizeof(int *));
    for(int i=0;i<n;i++){
        dist[i] = (int *)malloc(m * sizeof(int));
        for(int j=0;j<m;j++) dist[i][j] = -1;
    }
    
    int queue_size = n * m;
    Point *queue = (Point *)malloc(queue_size * sizeof(Point));
    int head = 0, tail = 0;
    
    dist[x][y] = 0;
    queue[tail++] = (Point){x, y};
    
    int dirs[8][2] = {
        {2, 1}, {1, 2}, {-1,2}, {-2,1},
        {-2,-1}, {-1,-2}, {1,-2}, {2,-1}
    };
    
    while(head < tail){
        Point current = queue[head++];
        int d = dist[current.x][current.y];
        for(int i=0;i<8;i++){
            int nx = current.x + dirs[i][0];
            int ny = current.y + dirs[i][1];
            if(nx >=0 && nx < n && ny >=0 && ny < m && dist[nx][ny]==-1){
                dist[nx][ny] = d +1;
                queue[tail++] = (Point){nx, ny};
            }
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d", dist[i][j]);
            if(j != m-1) printf(" ");
        }
        printf("\n");
    }
    
    for(int i=0;i<n;i++) free(dist[i]);
    free(dist);
    free(queue);
    return 0;
}