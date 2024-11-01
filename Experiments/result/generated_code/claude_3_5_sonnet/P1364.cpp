#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 101

typedef struct {
    int population;
    int left;
    int right;
} Node;

Node tree[MAX_N];
int n;
long long total_population = 0;
long long subtree_population[MAX_N] = {0};
long long min_distance = LLONG_MAX;

void dfs(int node, int depth) {
    subtree_population[node] = tree[node].population;
    
    if (tree[node].left) {
        dfs(tree[node].left, depth + 1);
        subtree_population[node] += subtree_population[tree[node].left];
    }
    
    if (tree[node].right) {
        dfs(tree[node].right, depth + 1);
        subtree_population[node] += subtree_population[tree[node].right];
    }
}

void calculate_distance(int node, long long up_distance) {
    long long current_distance = up_distance + (total_population - subtree_population[node]);
    
    if (current_distance < min_distance) {
        min_distance = current_distance;
    }
    
    if (tree[node].left) {
        calculate_distance(tree[node].left, current_distance + subtree_population[node] - subtree_population[tree[node].left]);
    }
    
    if (tree[node].right) {
        calculate_distance(tree[node].right, current_distance + subtree_population[node] - subtree_population[tree[node].right]);
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &tree[i].population, &tree[i].left, &tree[i].right);
        total_population += tree[i].population;
    }
    
    dfs(1, 0);
    calculate_distance(1, 0);
    
    printf("%lld\n", min_distance);
    
    return 0;
}