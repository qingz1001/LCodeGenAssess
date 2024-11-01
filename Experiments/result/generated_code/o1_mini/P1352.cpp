#include <stdio.h>
#include <stdlib.h>

#define MAXN 6001

long long dp0[MAXN];
long long dp1[MAXN];
int first_child[MAXN];
int edge_to[6001];
int edge_next[6001];
int boss_node[MAXN];
int r_value[MAXN];
int stack_nodes[MAXN];
int visited_flag[MAXN];

int max_ll(long long a, long long b){
    return (a > b) ? a : b;
}

int main(){
    int n;
    scanf("%d", &n);
    
    for(int i=1; i<=n; i++){
        scanf("%d", &r_value[i]);
    }
    
    // Initialize
    for(int i=1; i<=n; i++){
        first_child[i] = -1;
        boss_node[i] = 0;
    }
    
    // Read n-1 edges
    int l, k;
    int edge_cnt = 0;
    for(int i=1; i<n; i++){
        scanf("%d %d", &l, &k);
        boss_node[l] = k;
        edge_cnt++;
        edge_to[edge_cnt] = l;
        edge_next[edge_cnt] = first_child[k];
        first_child[k] = edge_cnt;
    }
    
    // Find root
    int root = -1;
    for(int i=1; i<=n; i++){
        if(boss_node[i] == 0){
            root = i;
            break;
        }
    }
    
    // Iterative DFS using post-order
    int top = 0;
    stack_nodes[top++] = root;
    for(int i=0; i<top; i++){
        int node = stack_nodes[i];
        if(!visited_flag[node]){
            visited_flag[node] = 1;
            // Push children first
            for(int e = first_child[node]; e != -1; e = edge_next[e]){
                int child = edge_to[e];
                stack_nodes[top++] = child;
            }
        }
    }
    
    // Process nodes in reverse order
    for(int i=top-1; i>=0; i--){
        int node = stack_nodes[i];
        dp1[node] = r_value[node];
        for(int e = first_child[node]; e != -1; e = edge_next[e]){
            int child = edge_to[e];
            dp1[node] += dp0[child];
            if(dp0[child] > dp1[child]){
                dp0[node] += dp0[child];
            }
            else{
                dp0[node] += dp1[child];
            }
        }
    }
    
    long long answer = dp0[root] > dp1[root] ? dp0[root] : dp1[root];
    if(answer < 0){
        answer = 0;
    }
    printf("%lld\n", answer);
    return 0;
}