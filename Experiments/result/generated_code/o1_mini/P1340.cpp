#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

int cmp(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if(ea->w != eb->w)
        return ea->w - eb->w;
    if(ea->u != eb->u)
        return ea->u - eb->u;
    return ea->v - eb->v;
}

int parent[201];

int find_set(int x){
    if(parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

int main(){
    int N, W;
    scanf("%d %d", &N, &W);
    Edge edges[6001];
    int E = 0;
    for(int week = 0; week < W; week++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[E].u = u;
        edges[E].v = v;
        edges[E].w = w;
        E++;
        qsort(edges, E, sizeof(Edge), cmp);
        for(int i = 1; i <= N; i++) parent[i] = i;
        int count = 0;
        long long sum = 0;
        for(int i = 0; i < E && count < N-1; i++){
            int fu = find_set(edges[i].u);
            int fv = find_set(edges[i].v);
            if(fu != fv){
                parent[fu] = fv;
                sum += edges[i].w;
                count++;
            }
        }
        if(count == N-1)
            printf("%lld\n", sum);
        else
            printf("-1\n");
    }
    return 0;
}