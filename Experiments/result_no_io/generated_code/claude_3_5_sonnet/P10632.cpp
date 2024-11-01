#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 30000

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* adj[MAX_N];
int n;
double dp[MAX_N];

void add_edge(int u, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = v;
    node->next = adj[u];
    adj[u] = node;
}

double dfs(int u, int parent) {
    if (dp[u] >= 0) return dp[u];
    
    double sum = n;
    int count = 1;
    Node* v = adj[u];
    
    while (v) {
        if (v->id != parent) {
            double child = dfs(v->id, u);
            sum += child;
            count++;
        }
        v = v->next;
    }
    
    dp[u] = sum / count;
    return dp[u];
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        adj[i] = NULL;
        dp[i] = -1;
    }
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    
    double result = dfs(0, -1);
    printf("%.4f\n", result);
    
    return 0;
}