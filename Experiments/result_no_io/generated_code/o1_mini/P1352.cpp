#include<stdio.h>
#include<stdlib.h>

#define MAX 6001

int r[MAX];
int head[MAX];
int to_edge[MAX*2];
int next_edge[MAX*2];
int edge_cnt = 0;
int parent_arr[MAX];
long long dp0_arr[MAX];
long long dp1_arr[MAX];

void add_edge(int u, int v){
    to_edge[edge_cnt] = v;
    next_edge[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

int root = 0;

void dfs(int u){
    dp1_arr[u] = r[u];
    dp0_arr[u] = 0;
    for(int i = head[u]; i != -1; i = next_edge[i]){
        int v = to_edge[i];
        dfs(v);
        dp1_arr[u] += dp0_arr[v];
        if(dp0_arr[v] > dp1_arr[v]){
            dp0_arr[u] += dp0_arr[v];
        }
        else{
            dp0_arr[u] += dp1_arr[v];
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) {
        scanf("%d", &r[i]);
    }
    for(int i=1;i<=n;i++) {
        parent_arr[i] = 0;
    }
    for(int i=0;i<n;i++){
        int l, k;
        scanf("%d %d", &l, &k);
        parent_arr[l] = k;
        add_edge(k, l);
    }
    for(int i=1;i<=n;i++){
        if(parent_arr[i]==0){
            root = i;
            break;
        }
    }
    for(int i=0;i<=n;i++) head[i] = -1;
    edge_cnt = 0;
    for(int i=0;i<n;i++){
        int l, k;
        // Already read above
    }
    dfs(root);
    if(dp0_arr[root] > dp1_arr[root]){
        printf("%lld", dp0_arr[root]);
    }
    else{
        printf("%lld", dp1_arr[root]);
    }
    return 0;
}