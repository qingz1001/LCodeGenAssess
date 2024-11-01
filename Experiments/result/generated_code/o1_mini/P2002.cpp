#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 500005

typedef struct {
    int to;
    int next;
} Edge;

Edge adj[MAXM];
Edge rev_adj[MAXM];
int head[MAXN], rev_head[MAXN];
int edge_cnt = 0, rev_edge_cnt = 0;

void add_edge(int from, int to) {
    adj[edge_cnt].to = to;
    adj[edge_cnt].next = head[from];
    head[from] = edge_cnt++;
}

void add_rev_edge(int from, int to) {
    rev_adj[rev_edge_cnt].to = to;
    rev_adj[rev_edge_cnt].next = rev_head[from];
    rev_head[from] = rev_edge_cnt++;
}

int visited[MAXN];
int order[MAXN];
int order_cnt = 0;
int scc_id[MAXN];
int current_scc = 0;

void dfs1(int u){
    visited[u] = 1;
    for(int i = head[u]; i != -1; i = adj[i].next){
        int v = adj[i].to;
        if(!visited[v]){
            dfs1(v);
        }
    }
    order[order_cnt++] = u;
}

void dfs2(int u){
    scc_id[u] = current_scc;
    for(int i = rev_head[u]; i != -1; i = rev_adj[i].next){
        int v = rev_adj[i].to;
        if(scc_id[v]==-1){
            dfs2(v);
        }
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) { head[i] = -1; rev_head[i] = -1;}
    for(int i=0;i<m;i++){
        int b, e;
        scanf("%d %d", &b, &e);
        add_edge(b, e);
        add_rev_edge(e, b);
    }
    for(int i=1;i<=n;i++) {
        if(!visited[i]){
            dfs1(i);
        }
    }
    for(int i=1;i<=n;i++) scc_id[i] = -1;
    for(int i=order_cnt-1;i>=0;i--){
        int u = order[i];
        if(scc_id[u]==-1){
            dfs2(u);
            current_scc++;
        }
    }
    int *indegree = (int*)calloc(current_scc, sizeof(int));
    for(int u=1; u<=n; u++){
        for(int i = head[u]; i != -1; i = adj[i].next){
            int v = adj[i].to;
            if(scc_id[u] != scc_id[v]){
                indegree[scc_id[v]]++;
            }
        }
    }
    int res = 0;
    for(int i=0;i<current_scc;i++) {
        if(indegree[i]==0) res++;
    }
    printf("%d\n", res);
    free(indegree);
    return 0;
}