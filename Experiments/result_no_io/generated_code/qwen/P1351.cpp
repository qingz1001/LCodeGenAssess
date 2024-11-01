#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

int main() {
    int n;
    scanf("%d", &n);
    
    // Initialize adjacency list
    int *adj[n];
    for (int i = 0; i < n; ++i) {
        adj[i] = NULL;
    }
    
    // Read edges and build the graph
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v; // Convert to zero-based index
        
        // Add edge u -> v
        int *new_edge = (int *)malloc(sizeof(int));
        *new_edge = v;
        new_edge->next = adj[u];
        adj[u] = new_edge;
        
        // Add edge v -> u
        new_edge = (int *)malloc(sizeof(int));
        *new_edge = u;
        new_edge->next = adj[v];
        adj[v] = new_edge;
    }
    
    // Read weights
    int *weights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &weights[i]);
    }
    
    // Find all pairs with distance 2
    long long max_value = 0;
    long long sum_value = 0;
    
    for (int i = 0; i < n; ++i) {
        int w_i = weights[i];
        for (int *edge = adj[i]; edge != NULL; edge = edge->next) {
            int j = edge->val;
            for (int *edge_j = adj[j]; edge_j != NULL; edge_j = edge_j->next) {
                int k = edge_j->val;
                if (k != i && k != j) {
                    int w_k = weights[k];
                    long long value = (long long)w_i * w_k;
                    if (value > max_value) {
                        max_value = value;
                    }
                    sum_value = (sum_value + value) % MOD;
                }
            }
        }
    }
    
    printf("%lld %lld\n", max_value, sum_value);
    
    // Free allocated memory
    for (int i = 0; i < n; ++i) {
        while (adj[i] != NULL) {
            int *temp = adj[i];
            adj[i] = adj[i]->next;
            free(temp);
        }
    }
    free(weights);
    
    return 0;
}