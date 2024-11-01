#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000000

int main(){
    int R, C;
    if(scanf("%d %d", &R, &C)!=2){
        printf("Bad placement.\n");
        return 0;
    }
    // Allocate grid as 1D array
    char *grid = (char*)malloc(R * C * sizeof(char));
    if(!grid){
        printf("Bad placement.\n");
        return 0;
    }
    // Read the grid
    int count = 0;
    while(count < R * C){
        int ch = getchar();
        if(ch == EOF) break;
        if(ch == '.' || ch == '#'){
            grid[count++] = (char)ch;
        }
    }
    // Allocate labels
    int *labels = (int*)calloc(R * C, sizeof(int));
    if(!labels){
        free(grid);
        printf("Bad placement.\n");
        return 0;
    }
    // Initialize BFS queue
    int *queue_r = (int*)malloc(R * C * sizeof(int));
    int *queue_c = (int*)malloc(R * C * sizeof(int));
    if(!queue_r || !queue_c){
        free(grid);
        free(labels);
        free(queue_r);
        free(queue_c);
        printf("Bad placement.\n");
        return 0;
    }
    int front, rear;
    int ship_count = 0;
    int label_id = 1;
    int bad = 0;
    for(int i=0;i<R && !bad;i++){
        for(int j=0;j<C && !bad;j++){
            if(grid[i*C + j] == '#' && labels[i*C + j] == 0){
                // Start BFS
                front = 0;
                rear = 0;
                queue_r[rear] = i;
                queue_c[rear] = j;
                rear++;
                labels[i*C + j] = label_id;
                int min_r = i, max_r = i, min_c = j, max_c = j;
                while(front < rear){
                    int r = queue_r[front];
                    int c = queue_c[front];
                    front++;
                    // 4 directions
                    int dirs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
                    for(int d=0; d<4; d++){
                        int nr = r + dirs[d][0];
                        int nc = c + dirs[d][1];
                        if(nr >=0 && nr < R && nc >=0 && nc < C && grid[nr*C + nc] == '#' && labels[nr*C + nc] == 0){
                            labels[nr*C + nc] = label_id;
                            queue_r[rear] = nr;
                            queue_c[rear] = nc;
                            rear++;
                            if(nr < min_r) min_r = nr;
                            if(nr > max_r) max_r = nr;
                            if(nc < min_c) min_c = nc;
                            if(nc > max_c) max_c = nc;
                        }
                    }
                }
                ship_count++;
                int size_r = max_r - min_r +1;
                int size_c = max_c - min_c +1;
                if(size_r != size_c){
                    bad = 1;
                    break;
                }
                // Check all cells in bounding box
                for(int r = min_r; r <= max_r && !bad; r++){
                    for(int c = min_c; c <= max_c && !bad; c++){
                        if(grid[r*C + c] != '#'){
                            bad = 1;
                            break;
                        }
                    }
                }
                label_id++;
            }
        }
    }
    if(!bad){
        // Check adjacency
        for(int i=0;i<R && !bad;i++){
            for(int j=0;j<C && !bad;j++){
                if(grid[i*C + j] == '#'){
                    // Check down
                    if(i < R-1 && grid[(i+1)*C + j] == '#'){
                        if(labels[i*C + j] != labels[(i+1)*C + j]){
                            bad = 1;
                            break;
                        }
                    }
                    // Check right
                    if(j < C-1 && grid[i*C + (j+1)] == '#'){
                        if(labels[i*C + j] != labels[i*C + (j+1)]){
                            bad = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(bad){
        printf("Bad placement.\n");
    }
    else{
        printf("There are %d ships.\n", ship_count);
    }
    // Free memory
    free(grid);
    free(labels);
    free(queue_r);
    free(queue_c);
    return 0;
}