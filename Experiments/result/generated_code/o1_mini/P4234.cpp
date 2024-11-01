#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int u, v, w;
} Edge;

int cmp(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if(ea->w != eb->w) return ea->w - eb->w;
    if(ea->u != eb->u) return ea->u - eb->u;
    return ea->v - eb->v;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge *edges = (Edge*)malloc(sizeof(Edge)*m);
    for(int i=0;i<m;i++) scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    qsort(edges, m, sizeof(Edge), cmp);
    
    int left = 0, right = 10000, answer = -1;
    while(left <= right){
        int mid = (left + right) / 2;
        int found = 0;
        int i = 0, j = 0;
        // Initialize DSU
        int *parent = (int*)malloc(sizeof(int)*(n+1));
        for(int k=1;k<=n;k++) parent[k] = k;
        int cnt = n;
        while(i < m){
            // Reset DSU
            for(int k=1;k<=n;k++) parent[k] = k;
            cnt = n;
            // Find the window starting at i
            j = i;
            while(j < m && edges[j].w - edges[i].w <= mid){
                // Union
                // Find root
                int u = edges[j].u, v = edges[j].v;
                // Find with path compression
                int fu = u, fv = v;
                while(parent[fu] != fu) fu = parent[fu];
                while(parent[fv] != fv) fv = parent[fv];
                if(fu != fv){
                    parent[fu] = fv;
                    cnt--;
                }
                j++;
            }
            if(cnt == 1){
                found = 1;
                free(parent);
                break;
            }
            i++;
        }
        free(parent);
        if(found){
            answer = mid;
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%d\n", answer);
    free(edges);
    return 0;
}