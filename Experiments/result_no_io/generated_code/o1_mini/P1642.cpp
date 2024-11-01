#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 101
#define MAXK 101
#define INF -1e18

double w[MAXN];
double c_val[MAXN];
int adj[MAXN][MAXN];
int degree[MAXN];
int N, M;
double target;
double dp_tmp[MAXK];

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++) scanf("%lf", &w[i]);
    for(int i=1;i<=N;i++) scanf("%lf", &c_val[i]);
    for(int i=0;i<N-1;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][degree[a]++] = b;
        adj[b][degree[b]++] = a;
    }
    
    double low=0.0, high=10000.0, mid, eps=1e-5;
    
    // Tree DP
    // Returns the dp array for the subtree rooted at u
    // parent is the parent node to avoid revisiting
    // k_target is the required number of nodes
    // sum_ptr will hold the dp array
    double dp[MAXN][MAXK];
    
    while(high - low > eps){
        mid = (low + high) / 2.0;
        // Initialize dp
        for(int i=1;i<=N;i++) {
            for(int j=0;j<=N;j++) dp[i][j] = INF;
        }
        
        // Recursive DP
        // Implemented iteratively using stack
        // Stack stores nodes in post-order
        int stack[MAXN], top = -1;
        int parent_node[MAXN];
        memset(parent_node, 0, sizeof(parent_node));
        stack[++top] = 1;
        int visited[MAXN];
        memset(visited, 0, sizeof(visited));
        int post_order[MAXN];
        int po = 0;
        while(top >=0){
            int u = stack[top];
            if(!visited[u]){
                visited[u] = 1;
                for(int i=0;i<degree[u];i++) {
                    int v = adj[u][i];
                    if(v != parent_node[u]){
                        parent_node[v] = u;
                        stack[++top] = v;
                    }
                }
            }
            else{
                post_order[po++] = u;
                top--;
            }
        }
        
        // Initialize all dp to INF
        for(int i=1;i<=N;i++) {
            for(int j=0;j<=N;j++) dp[i][j] = INF;
        }
        
        // Process in post-order
        for(int i=0;i<po;i++){
            int u = post_order[i];
            dp[u][1] = w[u] - mid * c_val[u];
            for(int j=0;j<=N;j++) dp_tmp[j] = INF;
            for(int i_child=0;i_child<degree[u];i_child++){
                int v = adj[u][i_child];
                if(v == parent_node[u]) continue;
                // Combine dp[u] and dp[v]
                for(int a=1;a<=N;a++) {
                    if(dp[u][a] < INF){
                        for(int b=1;b<=N;b++){
                            if(dp[v][b] < INF && a + b <= N){
                                if(dp_tmp[a+b] < dp[u][a] + dp[v][b]){
                                    dp_tmp[a+b] = dp[u][a] + dp[v][b];
                                }
                            }
                        }
                    }
                }
                for(int k=1;k<=N;k++) {
                    if(dp_tmp[k] > dp[u][k]){
                        dp[u][k] = dp_tmp[k];
                    }
                }
            }
        }
        
        // After DP, check dp[1][N-M] >=0
        double res = dp[1][N-M];
        if(res >= -1e-9){
            low = mid;
        }
        else{
            high = mid;
        }
    }
    
    printf("%.1lf\n", low);
    return 0;
}