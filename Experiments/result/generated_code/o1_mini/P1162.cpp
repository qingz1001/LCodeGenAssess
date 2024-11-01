#include <stdio.h>
#include <string.h>

#define MAX 30

int n;
int grid[MAX][MAX];
int visited[MAX][MAX];
int queue[MAX * MAX][2];
int front, rear;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void enqueue(int x, int y){
    queue[rear][0] = x;
    queue[rear][1] = y;
    rear++;
}

int dequeue_x(){
    return queue[front][0];
}

int dequeue_y(){
    return queue[front][1];
}

int is_empty(){
    return front == rear;
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &grid[i][j]);
            visited[i][j] = 0;
        }
    }
    front = 0;
    rear = 0;
    // Enqueue all boundary 0s
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if((i == 0 || i == n-1 || j == 0 || j == n-1) && grid[i][j]==0 && !visited[i][j]){
                enqueue(i, j);
                visited[i][j] = 1;
            }
        }
    }
    // BFS
    while(!is_empty()){
        int x = dequeue_x();
        int y = dequeue_y();
        front++;
        for(int d=0;d<4;d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx >=0 && nx <n && ny >=0 && ny <n && grid[nx][ny]==0 && !visited[nx][ny]){
                enqueue(nx, ny);
                visited[nx][ny] = 1;
            }
        }
    }
    // Set enclosed 0s to 2
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]==0 && !visited[i][j]){
                grid[i][j] = 2;
            }
        }
    }
    // Print the grid
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d", grid[i][j]);
            if(j != n-1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}