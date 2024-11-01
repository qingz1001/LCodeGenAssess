#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int total_edges = 3 * n * (n +1)/2;
    int *edges = (int*)malloc(sizeof(int)*total_edges);
    for(int i=0;i<total_edges;i++) scanf("%d", &edges[i]);
    
    // Assign edge indices
    // Horizontal edges: 0 to h-1
    // Left edges: h to h + l -1
    // Right edges: h + l to total_edges -1
    int h = n*(n+1)/2;
    int l = h;
    int r = h;
    
    // Function to get horizontal edge index at row i, position j
    // i from 0 to n, j from 0 to i
    auto get_h = [&](int i, int j) -> int {
        return (i*(i+1))/2 + j;
    };
    
    // Function to get left edge index at row i, position j
    auto get_l = [&](int i, int j) -> int {
        return h + (i*(i+1))/2 + j;
    };
    
    // Function to get right edge index at row i, position j
    auto get_r = [&](int i, int j) -> int {
        return h + l + (i*(i+1))/2 + j;
    };
    
    int count=0;
    // Iterate through each small triangle
    // For upward triangles
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            // Edges: horizontal (i, j), left (i, j), right (i, j)
            int eh = get_h(i, j);
            int el = get_l(i, j);
            int er = get_r(i, j);
            if(edges[eh] && edges[el] && edges[er]){
                count++;
            }
        }
    }
    // For downward triangles
    for(int i=1;i<n;i++){
        for(int j=0;j<=i-1;j++){
            // Edges: horizontal (i, j), left (i, j+1), right (i, j)
            int eh = get_h(i, j);
            int el = get_l(i, j+1);
            int er = get_r(i, j);
            if(edges[eh] && edges[el] && edges[er]){
                count++;
            }
        }
    }
    printf("%d\n", count);
    free(edges);
    return 0;
}