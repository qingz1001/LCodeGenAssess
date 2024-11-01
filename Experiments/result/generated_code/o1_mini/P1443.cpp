#include <stdio.h>
#include <stdlib.h>

#define MAX 400

int main(){
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    int dist[MAX][MAX];
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            dist[i][j]=-1;
        }
    }
    int dx[8] = {2,1,-1,-2,-2,-1,1,2};
    int dy[8] = {1,2,2,1,-1,-2,-2,-1};
    // Queue implementation
    int queue_x[MAX*MAX];
    int queue_y[MAX*MAX];
    int front=0, back=0;
    x--; y--;
    dist[x][y]=0;
    queue_x[back]=x;
    queue_y[back]=y;
    back++;
    while(front < back){
        int cx = queue_x[front];
        int cy = queue_y[front];
        front++;
        for(int i=0;i<8;i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if(nx>=0 && nx<n && ny>=0 && ny<m && dist[nx][ny]==-1){
                dist[nx][ny]=dist[cx][cy]+1;
                queue_x[back]=nx;
                queue_y[back]=ny;
                back++;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d", dist[i][j]);
            if(j != m-1) printf("    ");
        }
        printf("\n");
    }
    return 0;
}