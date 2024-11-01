#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define MAXM 1000005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
char labels[MAXN];
char pattern[MAXM];
int fail[MAXM];
long long result;
int n, m;

// Function to add edge to adjacency list
void add_edge(int u, int v){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = v;
    edge->next = adj[u];
    adj[u] = edge;
}

// KMP failure function
void build_fail(){
    fail[0] = 0;
    for(int i=1;i<m;i++){
        int j = fail[i-1];
        while(j > 0 && pattern[i] != pattern[j]) j = fail[j-1];
        if(pattern[i] == pattern[j]) j++;
        fail[i] = j;
    }
}

// DFS to count the valid paths
long long cnt[MAXM];
void dfs(int u, int parent_node, int state){
    // Update state
    while(state > 0 && labels[u] != pattern[state]) state = fail[state-1];
    if(labels[u] == pattern[state]) state++;
    // If a full pattern is matched
    if(state == m){
        result += 1;
        state = fail[state-1];
    }
    // Add current state to count
    result += cnt[state];
    // Increment the count for current state
    cnt[state]++;
    // Traverse children
    for(Edge* edge = adj[u]; edge != NULL; edge = edge->next){
        if(edge->to != parent_node){
            dfs(edge->to, u, state);
        }
    }
    // Decrement the count after returning
    cnt[state]--;
}

int main(){
    int C;
    scanf("%d", &C);
    while(C--){
        // Read n and m
        scanf("%d %d", &n, &m);
        // Read labels
        scanf("%s", labels + 1);
        // Initialize adjacency list
        for(int i=1;i<=n;i++) adj[i] = NULL;
        // Read edges
        for(int i=1;i<n;i++){
            int u, v;
            scanf("%d %d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        // Read pattern
        scanf("%s", pattern);
        // Build failure function
        build_fail();
        // Initialize counts
        memset(cnt, 0, sizeof(long long)*(m));
        result = 0;
        // Start DFS from each node
        dfs(1, -1, 0);
        // Output result
        printf("%lld\n", result);
        // Free adjacency list
        for(int i=1;i<=n;i++){
            Edge* edge = adj[i];
            while(edge){
                Edge* tmp = edge;
                edge = edge->next;
                free(tmp);
            }
        }
    }
    return 0;
}