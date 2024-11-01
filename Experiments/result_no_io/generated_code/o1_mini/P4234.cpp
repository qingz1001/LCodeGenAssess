#include <stdio.h>
#include <stdlib.h>

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

typedef struct {
    int *parent;
    int *rank;
} UnionFind;

UnionFind* createUF(int n){
    UnionFind *uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->parent = (int*)malloc((n+1)*sizeof(int));
    uf->rank = (int*)malloc((n+1)*sizeof(int));
    for(int i=0;i<=n;i++){
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
    return uf;
}

void freeUF(UnionFind *uf){
    free(uf->parent);
    free(uf->rank);
    free(uf);
}

int find_set(UnionFind *uf, int x){
    if(uf->parent[x] != x)
        uf->parent[x] = find_set(uf, uf->parent[x]);
    return uf->parent[x];
}

void union_set(UnionFind *uf, int x, int y){
    int fx = find_set(uf, x);
    int fy = find_set(uf, y);
    if(fx == fy) return;
    if(uf->rank[fx] < uf->rank[fy]){
        uf->parent[fx] = fy;
    }
    else{
        uf->parent[fy] = fx;
        if(uf->rank[fx] == uf->rank[fy])
            uf->rank[fx]++;
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge *edges = (Edge*)malloc(m * sizeof(Edge));
    int min_w = 10001, max_w = 0;
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        if(edges[i].w < min_w) min_w = edges[i].w;
        if(edges[i].w > max_w) max_w = edges[i].w;
    }
    qsort(edges, m, sizeof(Edge), cmp);
    // Precompute start indices for each weight
    int *start_w = (int*)malloc((10001) * sizeof(int));
    int *end_w = (int*)malloc((10001) * sizeof(int));
    for(int w=0; w<=10000; w++){
        start_w[w] = m;
        end_w[w] = m;
    }
    for(int i=0;i<m;i++){
        if(start_w[edges[i].w] == m){
            start_w[edges[i].w] = i;
        }
        end_w[edges[i].w] = i+1;
    }
    // Binary search for the minimal difference
    int left = 0, right = max_w - min_w;
    int answer = right;
    while(left <= right){
        int mid = left + (right - left)/2;
        int feasible = 0;
        for(int w = min_w; w + mid <= max_w; w++){
            // Find the range [w, w+mid]
            int sw = w;
            int ew = w + mid;
            int start = start_w[sw];
            if(start == m) continue;
            // Find end
            int end = 0;
            if(ew > 10000) ew = 10000;
            if(ew <0) ew=0;
            end = end_w[ew];
            for(int ww = sw+1; ww <= ew; ww++){
                if(start_w[ww] < m && start_w[ww] < start)
                    start = start_w[ww];
            }
            // Adjust end to include all weights up to ew
            end = end_w[ew];
            // Initialize Union-Find
            UnionFind *uf = createUF(n);
            for(int i=start; i < end; i++){
                union_set(uf, edges[i].u, edges[i].v);
            }
            // Check connectivity
            int root = find_set(uf, 1);
            int connected = 1;
            for(int i=2;i<=n;i++){
                if(find_set(uf, i) != root){
                    connected = 0;
                    break;
                }
            }
            freeUF(uf);
            if(connected){
                feasible = 1;
                break;
            }
        }
        if(feasible){
            if(mid < answer){
                answer = mid;
            }
            right = mid -1;
        }
        else{
            left = mid +1;
        }
    }
    printf("%d\n", answer);
    free(edges);
    free(start_w);
    free(end_w);
    return 0;
}