#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Edge {
    int to;
    int rev;
    int cap;
} Edge;

typedef struct {
    Edge* edges;
    int size;
    int capacity;
} EdgeList;

void initEdgeList(EdgeList* list) {
    list->capacity = 4;
    list->size = 0;
    list->edges = (Edge*)malloc(sizeof(Edge) * list->capacity);
}

void addEdgeList(EdgeList* list, Edge edge) {
    if (list->size == list->capacity) {
        list->capacity *=2;
        list->edges = (Edge*)realloc(list->edges, sizeof(Edge)*list->capacity);
    }
    list->edges[list->size++] = edge;
}

int n, m, x;
EdgeList adj[201];
int level[201];
int ptr_[201];

int queue_[100000];
int front, rear;

void addEdge(int from, int to, int cap) {
    Edge a = {to, adj[to].size, cap};
    Edge b = {from, adj[from].size, 0};
    addEdgeList(&adj[from], a);
    addEdgeList(&adj[to], b);
}

int bfs(int s, int t){
    memset(level, -1, sizeof(int)*(n+1));
    front = rear =0;
    queue_[rear++] = s;
    level[s] =0;
    while(front < rear){
        int u = queue_[front++];
        for(int i=0;i<adj[u].size;i++){
            Edge e = adj[u].edges[i];
            if(e.cap >0 && level[e.to]==-1){
                level[e.to]=level[u]+1;
                queue_[rear++] = e.to;
                if(e.to == t) return 1;
            }
        }
    }
    return level[t]!=-1;
}

int dfs(int u, int t, int flow){
    if(u == t) return flow;
    for(int *p = &ptr_[u]; *p < adj[u].size; (*p)++){
        Edge *e = &adj[u].edges[*p];
        if(e->cap >0 && level[e->to]==level[u]+1){
            int pushed = dfs(e->to, t, flow < e->cap ? flow : e->cap);
            if(pushed >0){
                e->cap -= pushed;
                adj[e->to].edges[e->rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

long long maxFlow(int s, int t){
    long long flow =0;
    while(bfs(s,t)){
        memset(ptr_, 0, sizeof(int)*(n+1));
        while(1){
            int pushed = dfs(s,t, INT_MAX);
            if(pushed ==0) break;
            flow += pushed;
        }
    }
    return flow;
}

int main(){
    scanf("%d %d %d", &n, &m, &x);
    for(int i=1;i<=n;i++) initEdgeList(&adj[i]);
    for(int i=0;i<m;i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(a, b, c);
    }
    long long flow = maxFlow(1, n);
    if(flow ==0){
        printf("Orz Ni Jinan Saint Cow!\n");
        return 0;
    }
    long long batches = (x + flow -1)/flow;
    printf("%lld %lld\n", flow, batches);
    for(int i=1;i<=n;i++) free(adj[i].edges);
    return 0;
}