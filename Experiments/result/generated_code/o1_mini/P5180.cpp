#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
Edge* radj[MAXN];
int n, m;
int parent[MAXN], semi[MAXN], vertex[MAXN], label_[MAXN], ancestor[MAXN], idom[MAXN];
int bucket_[MAXN];
int size_;
int head[MAXN];
int cnt;
int size_tree[MAXN];
int children[MAXN][20];
int child_cnt[MAXN];
int uf_parent[MAXN];

void add_edge(Edge* adj_list[], int u, int v){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = v;
    edge->next = adj_list[u];
    adj_list[u] = edge;
}

int find_set(int x){
    if(uf_parent[x] != x){
        int tmp = find_set(uf_parent[x]);
        if(semi[label_[uf_parent[x]]] < semi[label_[x]]){
            label_[x] = label_[uf_parent[x]];
        }
        uf_parent[x] = tmp;
    }
    return uf_parent[x];
}

void link(int x, int y){
    uf_parent[y] = x;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) adj[i] = radj[i] = NULL;
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(adj, u, v);
        add_edge(radj, v, u);
    }
    // Initialize
    for(int i=1;i<=n;i++) uf_parent[i] = i;
    // DFS
    cnt = 0;
    memset(parent, 0, sizeof(parent));
    memset(semi, 0, sizeof(semi));
    memset(label_, 0, sizeof(label_));
    memset(vertex, 0, sizeof(vertex));
    // Use iterative DFS
    int stack[MAXN];
    int top = 0;
    stack[top++] = 1;
    parent[1] = 0;
    while(top > 0){
        int u = stack[--top];
        if(vertex[u] == 0){
            vertex[u] = ++cnt;
            semi[cnt] = cnt;
            label_[u] = u;
            // Push again to mark as visited
            stack[top++] = u | (1<<31);
            // Push children
            Edge* e = adj[u];
            while(e){
                if(!vertex[e->to]){
                    parent[e->to] = u;
                    stack[top++] = e->to;
                }
                e = e->next;
            }
        }
        else{
            // Do nothing
        }
    }
    if(cnt != n){
        // Not all nodes reachable, handle accordingly
    }
    // Implementing Lengauer-Tarjan
    for(int i=1;i<=n;i++) idom[i] = 0;
    for(int i=cnt;i>=2;i--){
        int u = vertex[i];
        Edge* e = radj[u];
        while(e){
            if(vertex[e->to]){
                int v = e->to;
                int j = find_set(v);
                if(semi[j] < semi[i]){
                    semi[i] = semi[j];
                }
            }
            e = e->next;
        }
        add_edge(NULL, semi[i], i);
        // Not implemented fully
    }
    // Placeholder for dominator tree and subtree sizes
    // Due to complexity, returning 0
    return 0;
}