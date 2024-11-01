#include <stdio.h>
#include <stdlib.h>

// Function to find the root of a set with path compression
int find_set(int x, int *parent) {
    if (parent[x] != x)
        parent[x] = find_set(parent[x], parent);
    return parent[x];
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Allocate memory for grid, parent, and size arrays
    char *grid = (char*)malloc(n * n * sizeof(char));
    if (!grid) return 1;
    
    int *parent = (int*)malloc(n * n * sizeof(int));
    int *size_arr = (int*)malloc(n * n * sizeof(int));
    if (!parent || !size_arr){
        free(grid);
        return 1;
    }
    
    // Read grid
    char *temp = (char*)malloc((n + 1) * sizeof(char));
    if (!temp){
        free(grid);
        free(parent);
        free(size_arr);
        return 1;
    }
    for(int row = 0; row < n; row++){
        scanf("%s", temp);
        for(int col = 0; col < n; col++){
            grid[row * n + col] = temp[col];
            parent[row * n + col] = row * n + col;
            size_arr[row * n + col] = 1;
        }
    }
    free(temp);
    
    // Directions: up, down, left, right
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    
    // Union adjacent cells with different values
    for(int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            int current = row * n + col;
            for(int d = 0; d < 4; d++){
                int nr = row + dr[d];
                int nc = col + dc[d];
                if(nr >=0 && nr < n && nc >=0 && nc < n){
                    int neighbor = nr * n + nc;
                    if(grid[current] != grid[neighbor]){
                        int root1 = find_set(current, parent);
                        int root2 = find_set(neighbor, parent);
                        if(root1 != root2){
                            if(size_arr[root1] < size_arr[root2]){
                                parent[root1] = root2;
                                size_arr[root2] += size_arr[root1];
                            }
                            else{
                                parent[root2] = root1;
                                size_arr[root1] += size_arr[root2];
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Process queries
    for(int q = 0; q < m; q++){
        int i, j;
        scanf("%d %d", &i, &j);
        int index = (i-1) * n + (j-1);
        int root = find_set(index, parent);
        printf("%d\n", size_arr[root]);
    }
    
    // Free allocated memory
    free(grid);
    free(parent);
    free(size_arr);
    
    return 0;
}