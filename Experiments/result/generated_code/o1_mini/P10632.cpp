#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef double db;

#define MAXN 30005

int n;
int head[MAXN], to[MAXN*2], nxt[MAXN*2];
int cnt = 0;

// Adding edges to the adjacency list
void add_edge(int u, int v){
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt++;
    to[cnt] = u;
    nxt[cnt] = head[v];
    head[v] = cnt++;
}

ll size_tree[MAXN];
db dp_val[MAXN];
int parent_node[MAXN];

// DFS to compute subtree sizes and parent
ll dfs_size(int u, int parent){
    size_tree[u] = 1;
    parent_node[u] = parent;
    for(int i = head[u]; i != -1; i = nxt[i]){
        int v = to[i];
        if(v != parent){
            size_tree[u] += dfs_size(v, u);
        }
    }
    return size_tree[u];
}

// DFS to compute dp values
db dfs_dp(int u){
    if(dp_val[u] > -0.5) return dp_val[u];
    if(head[u] == -1){
        dp_val[u] = 1.0;
        return dp_val[u];
    }
    db res = (db)size_tree[u];
    int children = 0;
    db sum = 0.0;
    for(int i = head[u]; i != -1; i = nxt[i]){
        int v = to[i];
        if(v != parent_node[u]){
            sum += dfs_dp(v);
            children++;
        }
    }
    if(children > 0){
        res += sum / size_tree[u];
    }
    dp_val[u] = res;
    return dp_val[u];
}

int main(){
    // Initialize
    for(int i=0;i<MAXN;i++) head[i]=-1;
    for(int i=0;i<MAXN;i++) dp_val[i]=-1.0;

    // Read input
    scanf("%d", &n);
    for(int i=0;i<n-1;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
    }

    // If n==0, output 0.0000
    if(n == 0){
        printf("0.0000\n");
        return 0;
    }

    // Choose node 0 as root
    dfs_size(0, -1);
    db result = dfs_dp(0);
    printf("%.4lf\n", result);
    return 0;
}