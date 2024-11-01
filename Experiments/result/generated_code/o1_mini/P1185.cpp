#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_M 10
#define MAX_NODES (1 << MAX_M)
#define MAX_COLS (2 * (1 << MAX_M) - 1)
#define MAX_ROWS (2 * MAX_M + 1)

int exists[ MAX_M +1 ][ MAX_NODES +1 ];
int node_x[ MAX_M +1 ][ MAX_NODES +1 ];
char grid[ MAX_ROWS ][ MAX_COLS +2 ];

int m, n;

// Function to mark a node and its subtree as deleted
void mark_deleted(int i, int j, int m_limit){
    if(i > m_limit) return;
    if(j <1 || j > (1 << (i-1))) return;
    if(!exists[i][j]) return;
    exists[i][j] = 0;
    mark_deleted(i+1, 2*j -1, m_limit);
    mark_deleted(i+1, 2*j, m_limit);
}

// Function to assign x positions using in-order traversal
void assign_x(int i, int j, int m_limit, int *current_x){
    if(i > m_limit) return;
    if(j <1 || j > (1 << (i-1))) return;
    if(!exists[i][j]) return;
    assign_x(i+1, 2*j -1, m_limit, current_x);
    node_x[i][j] = (*current_x)++;
    assign_x(i+1, 2*j, m_limit, current_x);
}

int main(){
    scanf("%d %d", &m, &n);
    // Initialize exists to 1
    for(int i=1;i<=m;i++) {
        for(int j=1;j<= (1<< (i-1));j++) {
            exists[i][j] =1;
        }
    }
    // Read deletions
    for(int k=0; k<n; k++){
        int del_i, del_j;
        scanf("%d %d", &del_i, &del_j);
        mark_deleted(del_i, del_j, m);
    }
    // Assign x positions
    int current_x =1;
    assign_x(1,1,m,&current_x);
    int max_x = current_x -1;
    // Initialize grid with spaces
    for(int r=0; r < 2*m +1; r++) {
        for(int c=0; c < (2*max_x); c++) {
            grid[r][c] = ' ';
        }
        grid[r][2*max_x] = '\0';
    }
    // Place 'o's
    for(int i=1;i<=m;i++) {
        for(int j=1; j<= (1<< (i-1)); j++) {
            if(exists[i][j] && node_x[i][j] >0){
                int row = 2*i -2;
                int col = 2*node_x[i][j] -2;
                grid[row][col] = 'o';
            }
        }
    }
    // Place '/' and '\'
    for(int i=1;i<=m;i++) {
        for(int j=1; j<= (1<< (i-1)); j++) {
            if(exists[i][j] && node_x[i][j] >0){
                // Left child
                if(i <m){
                    if(exists[i+1][2*j -1] && node_x[i+1][2*j -1] >0){
                        int parent_row = 2*i -2;
                        int parent_col = 2*node_x[i][j] -2;
                        int child_col = 2*node_x[i+1][2*j -1] -2;
                        grid[parent_row +1][parent_col -1] = '/';
                    }
                    // Right child
                    if(exists[i+1][2*j] && node_x[i+1][2*j] >0){
                        int parent_row = 2*i -2;
                        int parent_col = 2*node_x[i][j] -2;
                        int child_col = 2*node_x[i+1][2*j] -2;
                        grid[parent_row +1][parent_col +1] = '\\';
                    }
                }
            }
        }
    }
    // Print grid
    for(int r=0; r < 2*m; r++) {
        // Find last non-space character
        int last = -1;
        for(int c=0; c < (2*max_x); c++) {
            if(grid[r][c] != ' ') last =c;
        }
        if(last ==-1){
            printf("\n");
            continue;
        }
        for(int c=0; c <=last; c++) {
            printf("%c", grid[r][c]);
        }
        printf("\n");
    }
    return 0;
}