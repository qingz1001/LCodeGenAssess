#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* adj[MAXN];
long long size_subtree[MAXN];
long long dp[MAXN];
long long n;
long long res = 0;
long long ans = 0;
int ans_node = 0;

// Function to add an edge to the adjacency list
void addEdge(int a, int b){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = b;
    newNode->next = adj[a];
    adj[a] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->id = a;
    newNode->next = adj[b];
    adj[b] = newNode;
}

// First DFS to compute size_subtree and dp for root
long long dfs1(int u, int parent){
    size_subtree[u] = 1;
    dp[u] = 0;
    Node* ptr = adj[u];
    while(ptr){
        int v = ptr->id;
        if(v != parent){
            dp[u] += dfs1(v, u) + size_subtree[v];
            size_subtree[u] += size_subtree[v];
        }
        ptr = ptr->next;
    }
    return dp[u];
}

// Second DFS to compute dp for all nodes
void dfs2(int u, int parent){
    Node* ptr = adj[u];
    while(ptr){
        int v = ptr->id;
        if(v != parent){
            dp[v] = dp[u] - size_subtree[v] + (n - size_subtree[v]);
            if(dp[v] < ans || (dp[v] == ans && v < ans_node)){
                ans = dp[v];
                ans_node = v;
            }
            dfs2(v, u);
        }
        ptr = ptr->next;
    }
}

int main(){
    int a, b;
    scanf("%lld", &n);
    for(int i=0;i<n-1;i++){
        scanf("%d %d", &a, &b);
        addEdge(a, b);
    }
    // Initialize root as 1
    dfs1(1, -1);
    ans = dp[1];
    ans_node = 1;
    dfs2(1, -1);
    printf("%d %lld\n", ans_node, ans);
    // Free allocated memory
    for(int i=1;i<=n;i++){
        Node* ptr = adj[i];
        while(ptr){
            Node* temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return 0;
}