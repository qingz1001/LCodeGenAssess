#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXN 101
#define MAXM 120
#define INF -1000000

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    
    int adj[MAXN][MAXN];
    memset(adj, -1, sizeof(adj));
    
    int from, to, k;
    int involved[MAXN];
    memset(involved, 0, sizeof(involved));
    
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &from, &to, &k);
        adj[from][to] = k;
        involved[from] = 1;
        involved[to] = 1;
    }
    
    // Topological sort
    int in_degree[MAXN];
    memset(in_degree, 0, sizeof(in_degree));
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(adj[i][j]!=-1){
                in_degree[j]++;
            }
        }
    }
    
    int queue[MAXN], front=0, rear=0;
    for(int i=1;i<=n;i++) {
        if(in_degree[i]==0){
            queue[rear++] = i;
        }
    }
    
    int topo_order[MAXN];
    int idx=0;
    while(front < rear){
        int u = queue[front++];
        topo_order[idx++] = u;
        for(int v=1; v<=n; v++){
            if(adj[u][v]!=-1){
                in_degree[v]--;
                if(in_degree[v]==0){
                    queue[rear++] = v;
                }
            }
        }
    }
    
    // Check if DAG
    if(idx != n){
        // There is a cycle, but per problem statement, likely no cycles
    }
    
    // Longest path
    int dp[MAXN];
    for(int i=1;i<=n;i++) dp[i] = 0;
    
    for(int i=0;i<idx;i++){
        int u = topo_order[i];
        for(int v=1; v<=n; v++){
            if(adj[u][v]!=-1){
                if(dp[v] < dp[u] + adj[u][v]){
                    dp[v] = dp[u] + adj[u][v];
                }
            }
        }
    }
    
    // Find the maximum time
    int max_time = 0;
    for(int i=1;i<=n;i++) {
        if(involved[i] && dp[i] > max_time){
            max_time = dp[i];
        }
    }
    
    // Collect involved nodes
    int nodes[MAXN];
    int count=0;
    for(int i=1;i<=n;i++) {
        if(involved[i]){
            nodes[count++] = i;
        }
    }
    
    // Sort the nodes
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(nodes[i] > nodes[j]){
                int temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }
    }
    
    // Output
    printf("%d\n", max_time);
    for(int i=0;i<count;i++){
        printf("%d", nodes[i]);
        if(i != count-1) printf(" ");
    }
    printf("\n");
    
    return 0;
}