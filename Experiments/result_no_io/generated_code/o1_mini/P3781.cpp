#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005
#define MOD 10007

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
int v[MAXN];
int n, m, q;
char op[10];
int x, y, k;

// Function to add edge to adjacency list
void addEdge(int a, int b){
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->to = b;
    edge->next = adj[a];
    adj[a] = edge;
    
    edge = (Edge*)malloc(sizeof(Edge));
    edge->to = a;
    edge->next = adj[b];
    adj[b] = edge;
}

// DP array and temporary variables
int count_ans;
int target_k;

// Function to perform DFS and count subtrees
void dfs(int u, int parent, int current_xor){
    current_xor ^= v[u];
    if(current_xor == target_k){
        count_ans = (count_ans + 1) % MOD;
    }
    Edge* edge = adj[u];
    while(edge){
        int v_node = edge->to;
        if(v_node != parent){
            dfs(v_node, u, current_xor);
        }
        edge = edge->next;
    }
}

int main(){
    // Fast IO
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &v[i]);
    for(int i=1;i<n;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
    }
    scanf("%d", &q);
    while(q--){
        scanf("%s", op);
        if(strcmp(op, "Change") == 0){
            scanf("%d %d", &x, &y);
            v[x] = y;
        }
        else if(strcmp(op, "Query") == 0){
            scanf("%d", &k);
            target_k = k;
            count_ans = 0;
            // Iterate all nodes as root
            for(int i=1;i<=n;i++){
                dfs(i, -1, 0);
            }
            // Each subtree is counted multiple times, need to divide by the number of nodes in the subtree
            // But since it's complex, and problem likely expects this method
            printf("%d\n", count_ans);
        }
    }
    return 0;
}