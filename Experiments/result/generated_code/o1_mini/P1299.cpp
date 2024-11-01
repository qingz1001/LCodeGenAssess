#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_COORD 200
#define MAX_NODE 40000
#define MAX_ADJ 4

// Comparison function for qsort
int cmp_int(const void *a, const void *b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    if(ia < ib) return -1;
    if(ia > ib) return 1;
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    int x_list[2*MAX_N];
    int y_list[2*MAX_N];
    int x_count =0, y_count=0;
    int segments[MAX_N][4];
    for(int i=0;i<N;i++){
        scanf("%d %d %d %d", &segments[i][0], &segments[i][1], &segments[i][2], &segments[i][3]);
        x_list[x_count++] = segments[i][0];
        x_list[x_count++] = segments[i][2];
        y_list[y_count++] = segments[i][1];
        y_list[y_count++] = segments[i][3];
    }
    // Sort and remove duplicates
    qsort(x_list, x_count, sizeof(int), cmp_int);
    qsort(y_list, y_count, sizeof(int), cmp_int);
    int unique_x[MAX_COORD];
    int unique_y[MAX_COORD];
    int ux=0, uy=0;
    unique_x[ux++] = x_list[0];
    for(int i=1;i<x_count;i++) {
        if(x_list[i]!=x_list[i-1]){
            unique_x[ux++] = x_list[i];
        }
    }
    unique_y[uy++] = y_list[0];
    for(int i=1;i<y_count;i++) {
        if(y_list[i]!=y_list[i-1]){
            unique_y[uy++] = y_list[i];
        }
    }
    // Function to find index
    auto find_idx = [&](int* arr, int size, int val) -> int {
        int left=0, right=size-1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(arr[mid] == val) return mid;
            if(arr[mid] < val) left = mid +1;
            else right = mid -1;
        }
        return -1;
    };
    // Initialize edges
    int h_edge[MAX_COORD][MAX_COORD];
    int v_edge[MAX_COORD][MAX_COORD];
    for(int i=0;i<MAX_COORD;i++) {
        for(int j=0;j<MAX_COORD;j++) {
            h_edge[i][j]=0;
            v_edge[i][j]=0;
        }
    }
    // Mark edges
    for(int i=0;i<N;i++){
        int x1 = segments[i][0];
        int y1 = segments[i][1];
        int x2 = segments[i][2];
        int y2 = segments[i][3];
        if(y1 == y2){
            // Horizontal
            int yi = find_idx(unique_y, uy, y1);
            if(yi == -1) continue;
            int xmin = x1 < x2 ? x1 : x2;
            int xmax = x1 > x2 ? x1 : x2;
            for(int x = xmin; x < xmax; x++){
                int xi = find_idx(unique_x, ux, x);
                if(xi == -1) continue;
                h_edge[xi][yi] =1;
            }
        }
        else{
            // Vertical
            int xi = find_idx(unique_x, ux, x1);
            if(xi == -1) continue;
            int ymin = y1 < y2 ? y1 : y2;
            int ymax = y1 > y2 ? y1 : y2;
            for(int y = ymin; y < ymax; y++){
                int yi = find_idx(unique_y, uy, y);
                if(yi == -1) continue;
                v_edge[xi][yi] =1;
            }
        }
    }
    // Count E and mark used nodes
    long long E =0;
    int used_nodes[MAX_NODE];
    for(int i=0;i<MAX_NODE;i++) used_nodes[i]=0;
    for(int x=0; x<ux-1; x++){
        for(int y=0; y<uy; y++){
            if(h_edge[x][y]){
                E++;
                int u = x * uy + y;
                int v = (x+1)*uy + y;
                used_nodes[u]=1;
                used_nodes[v]=1;
            }
        }
    }
    for(int x=0; x<ux; x++){
        for(int y=0; y<uy-1; y++){
            if(v_edge[x][y]){
                E++;
                int u = x * uy + y;
                int v = x * uy + (y+1);
                used_nodes[u]=1;
                used_nodes[v]=1;
            }
        }
    }
    // Build adjacency list
    int adj_size[MAX_NODE];
    int adj[MAX_NODE][MAX_ADJ];
    for(int i=0;i<MAX_NODE;i++) adj_size[i]=0;
    for(int x=0; x<ux-1; x++){
        for(int y=0; y<uy; y++){
            if(h_edge[x][y]){
                int u = x * uy + y;
                int v = (x+1)*uy + y;
                if(adj_size[u] < MAX_ADJ){
                    adj[u][adj_size[u]++] = v;
                }
                if(adj_size[v] < MAX_ADJ){
                    adj[v][adj_size[v]++] = u;
                }
            }
        }
    }
    for(int x=0; x<ux; x++){
        for(int y=0; y<uy-1; y++){
            if(v_edge[x][y]){
                int u = x * uy + y;
                int v = x * uy + (y+1);
                if(adj_size[u] < MAX_ADJ){
                    adj[u][adj_size[u]++] = v;
                }
                if(adj_size[v] < MAX_ADJ){
                    adj[v][adj_size[v]++] = u;
                }
            }
        }
    }
    // DFS to count connected components
    int visited[MAX_NODE];
    for(int i=0;i<MAX_NODE;i++) visited[i]=0;
    int C=0;
    for(int i=0;i<MAX_NODE;i++) {
        if(used_nodes[i] && !visited[i]){
            C++;
            // Iterative DFS
            int stack[MAX_NODE];
            int top=0;
            stack[top++] = i;
            visited[i]=1;
            while(top >0){
                int current = stack[--top];
                for(int j=0; j<adj_size[current]; j++){
                    int neighbor = adj[current][j];
                    if(!visited[neighbor]){
                        visited[neighbor]=1;
                        stack[top++] = neighbor;
                    }
                }
            }
        }
    }
    // Count V
    int V=0;
    for(int i=0;i<MAX_NODE;i++) {
        if(used_nodes[i]) V++;
    }
    // Compute bounded faces
    long long bounded_faces = E - V + C;
    printf("%lld\n", bounded_faces);
    return 0;
}