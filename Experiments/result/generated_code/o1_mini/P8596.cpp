#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int parent;
    int rank;
} DSUElement;

int find_set(DSUElement *dsu, int x){
    if(dsu[x].parent != x){
        dsu[x].parent = find_set(dsu, dsu[x].parent);
    }
    return dsu[x].parent;
}

int main(){
    int W;
    scanf("%d", &W);
    int n, m;
    long long x;
    scanf("%d %d %lld", &n, &m, &x);
    // Read n points
    for(int i=0;i<n;i++){
        int xi, yi;
        scanf("%d %d", &xi, &yi);
    }
    // Read m edges
    Edge *edges = (Edge*)malloc(sizeof(Edge)*m);
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    // Initialize DSU
    DSUElement *dsu = (DSUElement*)malloc(sizeof(DSUElement)*(n+1));
    for(int i=1;i<=n;i++){
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }
    // Process edges with w <=x
    Edge *filtered = (Edge*)malloc(sizeof(Edge)*m);
    int cnt=0;
    for(int i=0;i<m;i++){
        if(edges[i].w <=x){
            filtered[cnt++] = edges[i];
            int fu = find_set(dsu, edges[i].u);
            int fv = find_set(dsu, edges[i].v);
            if(fu != fv){
                dsu[fu].parent = fv;
            }
        }
    }
    // Check connectivity
    int root = find_set(dsu, 1);
    int connected = 1;
    for(int i=2;i<=n;i++){
        if(find_set(dsu, i) != root){
            connected = 0;
            break;
        }
    }
    if(!connected){
        printf("0\n");
        return 0;
    }
    // Find an edge to increase
    Edge edge_to_increase;
    for(int i=0;i<cnt;i++){
        edge_to_increase = filtered[i];
        break;
    }
    long long needed = (long long)x +1 - edge_to_increase.w;
    if(needed <=0){
        needed =1;
    }
    // Ensure that the new w does not exceed 2^31-1
    if(edge_to_increase.w + needed > 2147483647){
        needed = 2147483647 - edge_to_increase.w;
    }
    // Compute popcount
    int pop = 0;
    long long temp = needed;
    while(temp){
        pop += temp &1;
        temp >>=1;
    }
    printf("1\n%d %d %lld\n", edge_to_increase.u, edge_to_increase.v, needed);
    free(edges);
    free(filtered);
    free(dsu);
    return 0;
}