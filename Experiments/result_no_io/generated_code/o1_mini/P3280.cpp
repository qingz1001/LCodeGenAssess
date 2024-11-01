#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define LOGN 17
#define INF 1000000000

typedef long long ll;

typedef struct Edge {
    int u, v;
    int w;
} Edge;

int cmp(const void *a, const void *b){
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    return eb->w - ea->w;
}

int parent[MAXN];
int find_set(int x){
    if(parent[x]!=x)
        parent[x]=find_set(parent[x]);
    return parent[x];
}

typedef struct Node {
    int to;
    int w;
    struct Node* next;
} Node;

Node* adj[MAXN];
int depth_node[MAXN];
int up[LOGN][MAXN];
int min_edge[LOGN][MAXN];

void add_edge(int u, int v, int w){
    Node* a = (Node*)malloc(sizeof(Node));
    a->to = v;
    a->w = w;
    a->next = adj[u];
    adj[u] = a;
    Node* b = (Node*)malloc(sizeof(Node));
    b->to = u;
    b->w = w;
    b->next = adj[v];
    adj[v] = b;
}

void dfs(int u, int parent_u){
    up[0][u] = parent_u;
    Node* ptr = adj[u];
    while(ptr){
        int v = ptr->to;
        if(v != parent_u){
            depth_node[v] = depth_node[u] + 1;
            min_edge[0][v] = ptr->w;
            dfs(v, u);
        }
        ptr = ptr->next;
    }
}

int get_min(int a, int b){
    return a < b ? a : b;
}

int query(int u, int v){
    if(u == v) return INF;
    int res = INF;
    if(depth_node[u] < depth_node[v]){
        int temp = u; u = v; v = temp;
    }
    for(int k = LOGN-1; k >=0; k--){
        if(depth_node[u] - (1<<k) >= depth_node[v]){
            res = get_min(res, min_edge[k][u]);
            u = up[k][u];
        }
    }
    if(u == v) return res;
    for(int k = LOGN-1; k >=0; k--){
        if(up[k][u] != -1 && up[k][u] != up[k][v]){
            res = get_min(res, min_edge[k][u]);
            res = get_min(res, min_edge[k][v]);
            u = up[k][u];
            v = up[k][v];
        }
    }
    res = get_min(res, min_edge[0][u]);
    res = get_min(res, min_edge[0][v]);
    return res;
}

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    int order_seq[n+1];
    for(int i=1;i<=n;i++) scanf("%d", &order_seq[i]);
    ll b[n+1];
    for(int i=1;i<=n;i++) scanf("%lld", &b[i]);
    Edge edges[m + (q*(q-1))/2 + 10];
    int edge_cnt =0;
    for(int i=0;i<m;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[edge_cnt].u = u;
        edges[edge_cnt].v = v;
        edges[edge_cnt].w = w;
        edge_cnt++;
    }
    int trains[q];
    for(int i=0;i<q;i++) scanf("%d", &trains[i]);
    // Add train edges as infinite
    for(int i=0;i<q;i++){
        for(int j=i+1;j<q;j++){
            edges[edge_cnt].u = trains[i];
            edges[edge_cnt].v = trains[j];
            edges[edge_cnt].w = INF;
            edge_cnt++;
        }
    }
    q = edge_cnt;
    qsort(edges, edge_cnt, sizeof(Edge), cmp);
    for(int i=1;i<=n;i++) parent[i]=i;
    for(int i=0;i<edge_cnt;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        int set_u = find_set(u);
        int set_v = find_set(v);
        if(set_u != set_v){
            parent[set_u] = set_v;
            add_edge(u, v, w);
        }
    }
    // Initialize LCA
    memset(up, -1, sizeof(up));
    memset(min_edge, 0, sizeof(min_edge));
    depth_node[1]=0;
    min_edge[0][1]=INF;
    dfs(1, -1);
    for(int k=1;k<LOGN;k++){
        for(int v=1; v<=n; v++){
            if(up[k-1][v] != -1){
                up[k][v] = up[k-1][up[k-1][v]];
                min_edge[k][v] = get_min(min_edge[k-1][v], min_edge[k-1][up[k-1][v]]);
            }
            else{
                up[k][v] = -1;
                min_edge[k][v] = min_edge[k-1][v];
            }
        }
    }
    // Find minimum capacity among consecutive orders
    ll min_cap = INF;
    for(int i=2;i<=n;i++){
        int u = order_seq[i-1];
        int v = order_seq[i];
        int cap = query(u, v);
        if(cap < min_cap) min_cap = cap;
    }
    // Calculate total buys and total sells
    ll total_buys =0, total_sells=0;
    for(int i=1;i<=n;i++){
        if(b[i] >0) total_buys += b[i];
        else total_sells += -b[i];
    }
    // The total to be traded is the minimum of total_buys, total_sells, min_cap
    ll total_trade = total_buys;
    if(total_trade > total_sells) total_trade = total_sells;
    if(total_trade > min_cap) total_trade = min_cap;
    // Now assign sells
    // Iterate and for each sell, assign min(b_i, remaining trade)
    ll remaining = total_trade;
    for(int i=1;i<=n;i++){
        if(b[i] <0){
            ll sell = (-b[i] < remaining) ? (-b[i]) : remaining;
            printf("%lld\n", sell);
            remaining -= sell;
            if(remaining ==0) {
                // For remaining sells, output 0
                for(int j=i+1;j<=n;j++) {
                    if(b[j]<0) printf("0\n");
                }
                return 0;
            }
        }
    }
    return 0;
}