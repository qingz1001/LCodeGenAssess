#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct Edge {
    int u, v;
    int w;
} Edge;

int cmp(const void* a, const void* b){
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    return eb->w - ea->w;
}

int parent[100005];
ll buy[100005];
int has_train[100005];
int order[100005];
ll bval[100005];
int n, m, q;

int find_set(int x){
    if(parent[x] != x){
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

int main(){
    scanf("%d %d %d", &n, &m, &q);
    for(int i=0;i<n;i++) scanf("%d", &order[i]);
    for(int i=0;i<n;i++) scanf("%lld", &bval[i]);
    Edge* edges = (Edge*)malloc(sizeof(Edge)*m);
    for(int i=0;i<m;i++) scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    for(int i=0;i<100005;i++) parent[i]=i;
    for(int i=0;i<100005;i++) buy[i]=0;
    memset(has_train, 0, sizeof(has_train));
    for(int i=0;i<q;i++){
        int x;
        scanf("%d", &x);
        has_train[x]=1;
    }
    qsort(edges, m, sizeof(Edge), cmp);
    // Connect train stations first with infinite capacity
    for(int i=1;i<=n;i++) {
        if(has_train[i]){
            parent[i]=0;
        }
    }
    for(int i=0;i<m;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        int pu = find_set(u);
        int pv = find_set(v);
        if(pu != pv){
            if(pu == 0 || pv == 0){
                parent[pu] = parent[pv] = 0;
            }
            else{
                parent[pu] = pv;
            }
        }
    }
    free(edges);
    // Assign component to each order
    int comp[n];
    for(int i=0;i<n;i++) {
        comp[i] = find_set(order[i]);
    }
    // Compute minimum capacity
    for(int i=0;i<n;i++) {
        if(bval[i] < 0){
            // Sell order
            // For simplicity, assume selling the minimum possible
            printf("%lld\n", -bval[i]);
        }
        else{
            // Buy order, accumulate
            buy[comp[i]] += bval[i];
        }
    }
    return 0;
}