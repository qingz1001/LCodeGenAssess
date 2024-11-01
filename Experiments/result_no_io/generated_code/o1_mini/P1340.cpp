#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
    int w;
} Edge;

// Union-Find functions with path compression
int find_set(int *parent, int x){
    if(parent[x] != x){
        parent[x] = find_set(parent, parent[x]);
    }
    return parent[x];
}

int main(){
    int N, W;
    scanf("%d %d", &N, &W);
    
    Edge edges[6000];
    int E = 0;
    
    for(int week = 0; week < W; week++){
        int new_u, new_v, new_w;
        scanf("%d %d %d", &new_u, &new_v, &new_w);
        
        // Binary search to find the insertion position
        int left = 0, right = E;
        while(left < right){
            int mid = left + (right - left) / 2;
            if(edges[mid].w <= new_w){
                left = mid + 1;
            }
            else{
                right = mid;
            }
        }
        // Shift elements to make space
        for(int i = E; i > left; i--){
            edges[i] = edges[i-1];
        }
        // Insert the new edge
        edges[left].u = new_u;
        edges[left].v = new_v;
        edges[left].w = new_w;
        E++;
        
        // Initialize Union-Find
        int parent[N+1];
        for(int i = 1; i <= N; i++) parent[i] = i;
        
        int count = N;
        long long total = 0;
        for(int i = 0; i < E; i++){
            int fu = find_set(parent, edges[i].u);
            int fv = find_set(parent, edges[i].v);
            if(fu != fv){
                parent[fu] = fv;
                total += edges[i].w;
                count--;
                if(count == 1) break;
            }
        }
        
        if(count == 1){
            printf("%lld\n", total);
        }
        else{
            printf("-1\n");
        }
    }
    
    return 0;
}