#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20001
#define MAX_M 100001

typedef struct Edge {
    int a, b;
    int c;
} Edge;

Edge edges[MAX_M];
int N, M;

int cmp_desc(const void *a, const void *b) {
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if (ea->c != eb->c)
        return eb->c - ea->c;
    if (ea->a != eb->a)
        return ea->a - eb->a;
    return ea->b - eb->b;
}

int color_arr[MAX_N];
int adj[MAX_N][100]; // Assuming max degree per node is less than 100
int adj_size[MAX_N];
int queue_[MAX_N];
int head, tail;

int is_bipartite(int X) {
    // Reset adjacency list
    for(int i=1;i<=N;i++) {
        adj_size[i]=0;
    }
    // Build graph with edges c > X
    for(int i=0;i<M;i++) {
        if(edges[i].c > X){
            adj[edges[i].a][adj_size[edges[i].a]++] = edges[i].b;
            adj[edges[i].b][adj_size[edges[i].b]++] = edges[i].a;
        }
    }
    // Initialize colors
    for(int i=1;i<=N;i++) color_arr[i] = -1;
    // BFS to check bipartite
    for(int i=1;i<=N;i++) {
        if(color_arr[i]==-1){
            color_arr[i]=0;
            head=0;
            tail=0;
            queue_[tail++] = i;
            while(head < tail){
                int u = queue_[head++];
                for(int j=0;j<adj_size[u];j++){
                    int v = adj[u][j];
                    if(color_arr[v]==-1){
                        color_arr[v] = color_arr[u]^1;
                        queue_[tail++] = v;
                    }
                    else if(color_arr[v] == color_arr[u]){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0;i<M;i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
    }
    // Sort edges in descending order of c
    qsort(edges, M, sizeof(Edge), cmp_desc);
    // Binary search
    int l=0, r=1000000000, ans=0;
    while(l <= r){
        int m = l + (r - l) / 2;
        if(is_bipartite(m)){
            ans = m;
            r = m - 1;
        }
        else{
            l = m + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}