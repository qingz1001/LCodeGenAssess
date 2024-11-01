#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20000
#define MAX_K 20000

struct Edge {
    int to, weight;
};

struct Node {
    struct Edge edges[MAX_K];
    int edge_count;
};

struct Node nodes[MAX_N + 1];
int n, initial_strength;
int amplifiers = 0;
int visited[MAX_N + 1];

void dfs(int node, int strength) {
    visited[node] = 1;
    
    for (int i = 0; i < nodes[node].edge_count; i++) {
        struct Edge edge = nodes[node].edges[i];
        if (!visited[edge.to]) {
            int new_strength = strength - edge.weight;
            if (new_strength <= 0) {
                amplifiers++;
                new_strength = initial_strength;
            }
            dfs(edge.to, new_strength);
        }
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        nodes[i].edge_count = k;
        for (int j = 0; j < k; j++) {
            int to, weight;
            scanf("%d %d", &to, &weight);
            nodes[i].edges[j].to = to;
            nodes[i].edges[j].weight = weight;
        }
    }
    
    scanf("%d", &initial_strength);
    
    dfs(1, initial_strength);
    
    int all_visited = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            all_visited = 0;
            break;
        }
    }
    
    if (all_visited) {
        printf("%d\n", amplifiers);
    } else {
        printf("No solution.\n");
    }
    
    return 0;
}