#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1001
#define INF 100000

int main(){
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);
    
    int hay[MAX][MAX];
    memset(hay, 0, sizeof(hay));
    
    for(int i=0;i<n;i++){
        int xi, yi;
        scanf("%d %d", &xi, &yi);
        hay[xi][yi] = 1;
    }
    
    int dist[MAX][MAX];
    for(int i=0;i<MAX;i++) {
        for(int j=0;j<MAX;j++) {
            dist[i][j] = INF;
        }
    }
    
    // Deque implementation
    int qx[10000000];
    int qy[10000000];
    int head=0, tail=0;
    
    dist[x0][y0] = 0;
    qx[tail] = x0;
    qy[tail] = y0;
    tail++;
    
    int dx[4] = {1, -1, 0, 0};
    int dy_dir[4] = {0, 0, 1, -1};
    
    while(head < tail){
        int x = qx[head];
        int y = qy[head];
        head++;
        
        if(x == 0 && y == 0){
            break;
        }
        
        for(int dir=0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy_dir[dir];
            
            if(nx >=0 && nx < MAX && ny >=0 && ny < MAX){
                int cost = dist[x][y] + hay[nx][ny];
                if(cost < dist[nx][ny]){
                    dist[nx][ny] = cost;
                    if(hay[nx][ny]){
                        qx[tail] = nx;
                        qy[tail] = ny;
                        tail++;
                    }
                    else{
                        head--;
                        qx[head] = nx;
                        qy[head] = ny;
                    }
                }
            }
        }
    }
    
    if(dist[0][0] < INF){
        printf("%d\n", dist[0][0]);
    }
    else{
        printf("-1\n");
    }
    
    return 0;
}