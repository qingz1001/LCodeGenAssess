#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10005
#define MAXM 50005
#define LOG 15

typedef struct {
    int u, v, w;
} Edge;

int cmp(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    if (eb->w != ea->w) return eb->w - ea->w;
    return 0;
}

int parent[MAXN];
int find_set(int x){
    if(parent[x] != x)
        parent[x] = find_set(parent[x]);
    return parent[x];
}

typedef struct {
    int to;
    int w;
    int next;
} Adj;

Adj adj[MAXM*2];
int head[MAXN];
int cnt = 0;

void add_edge(int u, int v, int w){
    adj[cnt].to = v;
    adj[cnt].w = w;
    adj[cnt].next = head[u];
    head[u] = cnt++;
}

int depth_node[MAXN];
int ancestor[MAXN][LOG];
int min_edge[MAXN][LOG];
int logn;

void dfs(int u, int fa, int w){
    ancestor[u][0] = fa;
    min_edge[u][0] = w;
    for(int i=1;i<LOG;i++){
        if(ancestor[u][i-1] != -1){
            ancestor[u][i] = ancestor[ancestor[u][i-1]][i-1];
            if(min_edge[u][i-1] < min_edge[ancestor[u][i-1]][i-1])
                min_edge[u][i] = min_edge[u][i-1];
            else
                min_edge[u][i] = min_edge[ancestor[u][i-1]][i-1];
        }
        else{
            ancestor[u][i] = -1;
            min_edge[u][i] = 0;
        }
    }
    for(int i=head[u]; i!=-1; i=adj[i].next){
        int v = adj[i].to;
        int weight = adj[i].w;
        if(v != fa){
            depth_node[v] = depth_node[u] + 1;
            dfs(v, u, weight);
        }
    }
}

int get_min(int u, int v){
    if(u == v) return -1;
    int res = 100000;
    if(depth_node[u] < depth_node[v]){
        int tmp = u;
        u = v;
        v = tmp;
    }
    for(int k=LOG-1; k>=0; k--){
        if(depth_node[u] - (1<<k) >= depth_node[v]){
            if(min_edge[u][k] < res) res = min_edge[u][k];
            u = ancestor[u][k];
        }
    }
    if(u == v){
        return res;
    }
    for(int k=LOG-1; k>=0; k--){
        if(ancestor[u][k] != -1 && ancestor[u][k] != ancestor[v][k]){
            if(min_edge[u][k] < res) res = min_edge[u][k];
            if(min_edge[v][k] < res) res = min_edge[v][k];
            u = ancestor[u][k];
            v = ancestor[v][k];
        }
    }
    if(ancestor[u][0] != -1 && ancestor[v][0] != -1){
        if(min_edge[u][0] < res) res = min_edge[u][0];
        if(min_edge[v][0] < res) res = min_edge[v][0];
        u = ancestor[u][0];
        v = ancestor[v][0];
    }
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Edge edges[MAXM];
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    qsort(edges, m, sizeof(Edge), cmp);
    for(int i=1;i<=n;i++) parent[i] = i;
    memset(head, -1, sizeof(head));
    for(int i=0;i<m;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        int pu = find_set(u);
        int pv = find_set(v);
        if(pu != pv){
            parent[pu] = pv;
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
    }
    memset(ancestor, -1, sizeof(ancestor));
    depth_node[1] = 0;
    // Find all roots
    for(int i=1;i<=n;i++){
        if(parent[i] == i && ancestor[i][0] == -1){
            dfs(i, -1, 0);
        }
    }
    int q;
    scanf("%d", &q);
    while(q--){
        int x, y;
        scanf("%d %d", &x, &y);
        if(find_set(x) != find_set(y)){
            printf("-1\n");
        }
        else{
            int ans = get_min(x, y);
            printf("%d\n", ans);
        }
    }
    return 0;
}