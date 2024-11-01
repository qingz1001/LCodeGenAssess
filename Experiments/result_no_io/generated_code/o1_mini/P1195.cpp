#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y, l;
} Edge;

int cmp(const void *a, const void *b) {
    Edge *ea = (Edge *)a;
    Edge *eb = (Edge *)b;
    if (ea->l != eb->l)
        return ea->l - eb->l;
    return 0;
}

int parent[1005];

int find_set(int x){
    if(parent[x]!=x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    Edge edges[M];
    for(int i=0;i<M;i++) scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].l);
    qsort(edges, M, sizeof(Edge), cmp);
    for(int i=1;i<=N;i++) parent[i]=i;
    int components = N;
    long long total = 0;
    for(int i=0;i<M;i++){
        int fx = find_set(edges[i].x);
        int fy = find_set(edges[i].y);
        if(fx != fy){
            parent[fx] = fy;
            total += edges[i].l;
            components--;
            if(components == K) break;
        }
    }
    // After processing, check if components == K
    // To ensure connectivity, we might need to continue
    // But in this approach, if components > K after all edges, no answer
    // Or if components < K, already achieved
    // So better recount the components
    // Re-initialize parent
    for(int i=1;i<=N;i++) parent[i]=i;
    for(int i=0;i<M;i++){
        int fx = find_set(edges[i].x);
        int fy = find_set(edges[i].y);
        if(fx != fy){
            parent[fx] = fy;
        }
    }
    // Count total connected components
    int final_components = 0;
    for(int i=1;i<=N;i++) {
        if(parent[i] == i) final_components++;
    }
    if(final_components > K){
        printf("No Answer\n");
        return 0;
    }
    // Now perform Krusky again
    for(int i=1;i<=N;i++) parent[i]=i;
    components = N;
    total = 0;
    for(int i=0;i<M;i++){
        int fx = find_set(edges[i].x);
        int fy = find_set(edges[i].y);
        if(fx != fy){
            parent[fx] = fy;
            total += edges[i].l;
            components--;
            if(components == K) break;
        }
    }
    if(components == K){
        printf("%lld\n", total);
    }
    else{
        printf("No Answer\n");
    }
}