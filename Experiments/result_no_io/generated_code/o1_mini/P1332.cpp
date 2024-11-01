#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Query;

int main(){
    int n, m, a, b;
    scanf("%d %d %d %d", &n, &m, &a, &b);
    
    int *grid = (int*)malloc(n * m * sizeof(int));
    for(int i = 0; i < n * m; i++) grid[i] = -1;
    
    int *queue = (int*)malloc(n * m * sizeof(int));
    int head = 0, tail = 0;
    
    for(int i = 0; i < a; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        int pos = (x-1)*m + (y-1);
        if(grid[pos]==-1){
            grid[pos]=0;
            queue[tail++] = pos;
        }
    }
    
    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    while(head < tail){
        int pos = queue[head++];
        int x = pos / m;
        int y = pos % m;
        int current_time = grid[pos];
        for(int d = 0; d < 4; d++){
            int nx = x + dirs[d][0];
            int ny = y + dirs[d][1];
            if(nx >=0 && nx < n && ny >=0 && ny < m){
                int npos = nx * m + ny;
                if(grid[npos]==-1){
                    grid[npos] = current_time +1;
                    queue[tail++] = npos;
                }
            }
        }
    }
    
    Query *queries = (Query*)malloc(b * sizeof(Query));
    for(int i = 0; i < b; i++) {
        scanf("%d %d", &queries[i].x, &queries[i].y);
    }
    
    for(int i = 0; i < b; i++){
        int pos = (queries[i].x -1)*m + (queries[i].y -1);
        printf("%d\n", grid[pos]);
    }
    
    free(grid);
    free(queue);
    free(queries);
    return 0;
}