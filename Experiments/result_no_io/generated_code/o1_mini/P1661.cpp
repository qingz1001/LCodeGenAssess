#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int u;
    int v;
    long long w;
} Edge;

int cmp(const void* a, const void* b){
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if(ea->w < eb->w) return -1;
    if(ea->w > eb->w) return 1;
    return 0;
}

long long absll(long long x){
    return x < 0 ? -x : x;
}

int main(){
    int n;
    scanf("%d", &n);
    long long x[n], y[n];
    for(int i=0;i<n;i++) scanf("%lld %lld", &x[i], &y[i]);
    int m = n*(n-1)/2;
    Edge edges[m];
    int idx = 0;
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            edges[idx].u = i;
            edges[idx].v = j;
            edges[idx].w = absll(x[i]-x[j]) + absll(y[i]-y[j]);
            idx++;
        }
    }
    qsort(edges, m, sizeof(Edge), cmp);
    int parent[n];
    for(int i=0;i<n;i++) parent[i] = i;
    int find_set(int a){
        if(parent[a] != a) parent[a] = find_set(parent[a]);
        return parent[a];
    }
    long long max_w = 0;
    for(int i=0;i<m;i++){
        int fu = find_set(edges[i].u);
        int fv = find_set(edges[i].v);
        if(fu != fv){
            parent[fu] = fv;
            if(edges[i].w > max_w) max_w = edges[i].w;
            n--;
            if(n == 1) break;
        }
    }
    long long t = (max_w + 1) / 2;
    printf("%lld\n", t);
    return 0;
}