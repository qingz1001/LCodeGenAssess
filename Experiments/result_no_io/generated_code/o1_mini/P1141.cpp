#include <stdio.h>
#include <stdlib.h>

int find_set(int *parent, int x){
    if(parent[x] != x){
        parent[x] = find_set(parent, parent[x]);
    }
    return parent[x];
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char *grid = (char*)malloc(n * n * sizeof(char));
    for(int i = 0; i < n; i++){
        scanf("%s", &grid[i * n]);
    }
    int total = n * n;
    int *parent = (int*)malloc(total * sizeof(int));
    int *size_set = (int*)malloc(total * sizeof(int));
    for(int i = 0; i < total; i++){
        parent[i] = i;
        size_set[i] = 1;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int current = i * n + j;
            // Right neighbor
            if(j + 1 < n){
                int right = i * n + (j + 1);
                if(grid[current] != grid[right]){
                    int root1 = find_set(parent, current);
                    int root2 = find_set(parent, right);
                    if(root1 != root2){
                        parent[root2] = root1;
                        size_set[root1] += size_set[root2];
                    }
                }
            }
            // Down neighbor
            if(i + 1 < n){
                int down = (i + 1) * n + j;
                if(grid[current] != grid[down]){
                    int root1 = find_set(parent, current);
                    int root2 = find_set(parent, down);
                    if(root1 != root2){
                        parent[root2] = root1;
                        size_set[root1] += size_set[root2];
                    }
                }
            }
        }
    }
    for(int q = 0; q < m; q++){
        int x, y;
        scanf("%d %d", &x, &y);
        int idx = (x - 1) * n + (y - 1);
        int root = find_set(parent, idx);
        printf("%d\n", size_set[root]);
    }
    free(grid);
    free(parent);
    free(size_set);
    return 0;
}