#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

typedef struct {
    int m, n, k;
    char grid[MAX][MAX + 1];
    int visited[MAX][MAX];
} Grid;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int valid(int x, int y, int m, int n) {
    return x >=0 && x < m && y >=0 && y < n;
}

void shuffle(int *array, int n) {
    for(int i = n-1;i>0;i--){
        int j = rand() % (i+1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main(){
    srand(time(NULL));
    Grid g;
    scanf("%d %d %d", &g.m, &g.n, &g.k);
    for(int i=0;i<g.m;i++) {
        scanf("%s", g.grid[i]);
    }
    
    // Initialize visited
    for(int i=0;i<g.m;i++) {
        for(int j=0;j<g.n;j++) {
            g.visited[i][j] = 0;
        }
    }
    
    // Find starting point
    int start_x = -1, start_y = -1;
    for(int i=0;i<g.m && start_x==-1;i++) {
        for(int j=0;j<g.n && start_x==-1;j++) {
            if(g.grid[i][j] == '.') {
                start_x = i;
                start_y = j;
            }
        }
    }
    
    if(start_x == -1){
        // No empty cells
        for(int i=0;i<g.m;i++) {
            printf("%s\n", g.grid[i]);
        }
        return 0;
    }
    
    // DFS stack
    int stack_x[MAX*MAX], stack_y[MAX*MAX];
    int top = 0;
    stack_x[top] = start_x;
    stack_y[top] = start_y;
    g.visited[start_x][start_y] = 1;
    
    while(top >=0){
        int x = stack_x[top];
        int y = stack_y[top];
        
        // Shuffle directions
        int dirs[4] = {0,1,2,3};
        shuffle(dirs,4);
        
        int moved = 0;
        for(int i=0;i<4;i++){
            int nx = x + dx[dirs[i]];
            int ny = y + dy[dirs[i]];
            if(valid(nx, ny, g.m, g.n) && g.grid[nx][ny] == '.' && !g.visited[nx][ny]){
                // Check if it can be connected
                int neighbors = 0;
                for(int d=0;d<4;d++){
                    int adjx = nx + dx[d];
                    int adjy = ny + dy[d];
                    if(valid(adjx, adjy, g.m, g.n) && g.grid[adjx][adjy] == '.' && g.visited[adjx][adjy]){
                        neighbors++;
                    }
                }
                if(neighbors <=1){
                    top++;
                    stack_x[top] = nx;
                    stack_y[top] = ny;
                    g.visited[nx][ny] = 1;
                    moved =1;
                    break;
                }
            }
        }
        if(!moved){
            top--;
        }
    }
    
    // Mark unvisited '.' as 'X'
    for(int i=0;i<g.m;i++) {
        for(int j=0;j<g.n;j++) {
            if(g.grid[i][j] == '.' && !g.visited[i][j]){
                g.grid[i][j] = 'X';
            }
        }
    }
    
    // Now ensure the maze has unique paths (already a tree)
    // Output the grid
    for(int i=0;i<g.m;i++) {
        printf("%s\n", g.grid[i]);
    }
    
    return 0;
}