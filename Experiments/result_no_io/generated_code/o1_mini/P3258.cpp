#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define LOG 19

int n;
int a[MAXN];
int parent[LOG][MAXN];
int depth_node[MAXN];
int adj[MAXN][2*LOG]; // Using dynamic adjacency list
int adj_size[MAXN];
int freq_cnt[MAXN];
int stack_ptr;
int stack_nodes[MAXN];
int lca(int u, int v) {
    if(depth_node[u] < depth_node[v]){
        int temp = u;
        u = v;
        v = temp;
    }
    for(int k=LOG-1;k>=0;k--){
        if(depth_node[u] - (1<<k) >= depth_node[v]){
            u = parent[k][u];
        }
    }
    if(u == v) return u;
    for(int k=LOG-1;k>=0;k--){
        if(parent[k][u] != -1 && parent[k][u] != parent[k][v]){
            u = parent[k][u];
            v = parent[k][v];
        }
    }
    return parent[0][u];
}

void dfs(int u, int p_node){
    parent[0][u] = p_node;
    for(int k=1;k<LOG;k++){
        if(parent[k-1][u] != -1){
            parent[k][u] = parent[k-1][parent[k-1][u]];
        }
        else{
            parent[k][u] = -1;
        }
    }
    for(int i=0;i<adj_size[u];i++){
        int v = adj[u][i];
        if(v != p_node){
            depth_node[v] = depth_node[u] + 1;
            dfs(v, u);
        }
    }
}

void accumulate_freq(int u, int p_node){
    for(int i=0;i<adj_size[u];i++){
        int v = adj[u][i];
        if(v != p_node){
            accumulate_freq(v, u);
            freq_cnt[u] += freq_cnt[v];
        }
    }
}

int main(){
    // Fast IO
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    for(int i=1;i<=n-1;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x][adj_size[x]++] = y;
        adj[y][adj_size[y]++] = x;
    }
    memset(parent, -1, sizeof(parent));
    depth_node[1] = 0;
    dfs(1, -1);
    for(int i=1;i<n;i++){
        int u = a[i];
        int v = a[i+1];
        int anc = lca(u, v);
        freq_cnt[u]++;
        freq_cnt[v]++;
        freq_cnt[anc] -=2;
    }
    accumulate_freq(1, -1);
    // Candies: freq[u] + (u == a1) - (u == an)
    for(int u=1; u<=n; u++){
        if(u == a[1]) freq_cnt[u]++;
        if(u == a[n]) freq_cnt[u]--;
    }
    for(int u=1; u<=n; u++) printf("%d\n", freq_cnt[u] >=0 ? freq_cnt[u] : 0);
    return 0;
}