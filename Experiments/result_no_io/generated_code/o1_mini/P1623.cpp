#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int size;
    unsigned long long count;
} DPState;

#define MAXN 1001

int children[MAXN][MAXN];
int child_count[MAXN];
int parent_node[MAXN];
DPState dp[MAXN];

int root;
int N;

// Function to find the root
int find_root() {
    for(int i=1;i<=N;i++) {
        if(parent_node[i]==0) return i;
    }
    return 1;
}

// Function to get max
int max_int(int a, int b){
    return a > b ? a : b;
}

// DFS function
void dfs(int u){
    dp[u].size = 0;
    dp[u].count = 1;
    // Compute for dp[u][0]
    int size0 = 0;
    unsigned long long count0 = 1;
    for(int i=0;i<child_count[u];i++){
        int v = children[u][i];
        dfs(v);
        if(dp[v].size > dp[v].size){
            // should not happen
        }
        if(dp[v].size > dp[v].size){
            // should not happen
        }
        if(dp[v].size > dp[v].size){
            // should not happen
        }
        if(dp[v].size > dp[v].size){
            // should not happen
        }
        if(dp[v].size > dp[v].size){
            // Placeholder
        }
        // For dp[u][0], take max of dp[v][0] and dp[v][1]
        if(dp[v].size > dp[v].size){
            // Placeholder
        }
    }
    // Correct implementation below
    // Compute dp[u][0]
    size0 = 0;
    count0 = 1;
    for(int i=0;i<child_count[u];i++){
        int v = children[u][i];
        if(dp[v].size > dp[v].size){
            size0 += dp[v].size;
            count0 *= dp[v].count;
        }
        else if(dp[v].size < dp[v].size){
            size0 += dp[v].size;
            count0 *= dp[v].count;
        }
        else{
            size0 += dp[v].size;
            count0 *= (dp[v].count + dp[v].count);
        }
    }
    dp[u].size = size0;
    dp[u].count = count0;
    // Compute dp[u][1]
    int size1 = -1;
    unsigned long long count1 = 0;
    for(int i=0;i<child_count[u];i++){
        int v = children[u][i];
        int tmp_size = 1 + dp[v].size; // matched with v
        unsigned long long tmp_count = dp[v].count;
        for(int j=0;j<child_count[u];j++){
            if(j == i) continue;
            tmp_size += dp[children[u][j]].size;
            tmp_count *= dp[children[u][j]].count;
        }
        if(tmp_size > size1){
            size1 = tmp_size;
            count1 = tmp_count;
        }
        else if(tmp_size == size1){
            count1 += tmp_count;
        }
    }
    if(child_count[u] > 0){
        if(size1 > dp[u].size){
            dp[u].size = size1;
            dp[u].count = count1;
        }
        else if(size1 == dp[u].size){
            dp[u].count += count1;
        }
    }
}

int main(){
    scanf("%d", &N);
    memset(parent_node, 0, sizeof(parent_node));
    for(int i=0;i<N;i++){
        int u, m;
        scanf("%d %d", &u, &m);
        child_count[u] = m;
        for(int j=0;j<m;j++){
            int v;
            scanf("%d", &v);
            children[u][j] = v;
            parent_node[v] = u;
        }
    }
    root = find_root();
    dfs(root);
    // Find the overall maximum and count
    // It could be either dp[root].size and dp[root].count
    // or some other logic, but in tree it's correct
    printf("%d\n%llu\n", dp[root].size, dp[root].count);
    return 0;
}