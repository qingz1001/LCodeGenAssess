#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 888
#define MAX_SIZE (2 * MAX_N + 2)
#define MAX_VERTICES ((2 * MAX_N + 2) * (2 * MAX_N + 2))

typedef struct {
    int next;
} Edge;

int main(){
    int n;
    scanf("%d", &n);
    int size = 2 * n +1;
    char grid[MAX_SIZE][MAX_SIZE];
    for(int i=0;i<2*n;i++){
        scanf(" %[^\n]", grid[i]);
    }
    // Assign unique id to each vertex
    // vertex_id = row * size + col
    // Initialize adjacency
    int *adj = (int*)calloc(MAX_VERTICES * MAX_VERTICES, sizeof(int));
    for(int i=0;i<2*n;i++){
        int row = i;
        int line_len = strlen(grid[i]);
        int start = (2*n - line_len)/2;
        for(int j=0; j<line_len; j++){
            char c = grid[i][j];
            int col = start + j;
            if(c == '/'){
                // '/' connects (row, col+1) to (row+1, col)
                int v1 = row * size + (col+1);
                int v2 = (row+1) * size + col;
                adj[v1 * MAX_VERTICES + v2] = 1;
                adj[v2 * MAX_VERTICES + v1] = 1;
            }
            else if(c == '\\'){
                // '\' connects (row, col) to (row+1, col+1)
                int v1 = row * size + col;
                int v2 = (row+1) * size + (col+1);
                adj[v1 * MAX_VERTICES + v2] = 1;
                adj[v2 * MAX_VERTICES + v1] = 1;
            }
        }
    }
    // Count parallelograms
    long long count = 0;
    for(int v1=0; v1 < size*size; v1++){
        for(int v2=v1+1; v2 < size*size; v2++){
            if(adj[v1 * MAX_VERTICES + v2]){
                for(int v3=v2+1; v3 < size*size; v3++){
                    if(adj[v1 * MAX_VERTICES + v3]){
                        for(int v4=v3+1; v4 < size*size; v4++){
                            if(adj[v2 * MAX_VERTICES + v4] && adj[v3 * MAX_VERTICES + v4]){
                                // Check if no internal edges
                                // This is simplified and may not cover all cases
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%lld\n", count);
    free(adj);
    return 0;
}