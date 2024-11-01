#include <stdio.h>
#include <stdlib.h>

#define MAX_N 101

typedef struct Node {
    int weight;
    int left;
    int right;
} Node;

Node tree[MAX_N];
int n;
long long total_weight = 0;
long long subtree_weight[MAX_N] = {0};
long long min_distance = 1e18;

void dfs1(int node) {
    subtree_weight[node] = tree[node].weight;
    if (tree[node].left) {
        dfs1(tree[node].left);
        subtree_weight[node] += subtree_weight[tree[node].left];
    }
    if (tree[node].right) {
        dfs1(tree[node].right);
        subtree_weight[node] += subtree_weight[tree[node].right];
    }
}

void dfs2(int node, long long upper_weight) {
    long long current_distance = total_weight - subtree_weight[node] + upper_weight;
    if (current_distance < min_distance) {
        min_distance = current_distance;
    }
    
    if (tree[node].left) {
        dfs2(tree[node].left, upper_weight + subtree_weight[node] - subtree_weight[tree[node].left]);
    }
    if (tree[node].right) {
        dfs2(tree[node].right, upper_weight + subtree_weight[node] - subtree_weight[tree[node].right]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &tree[i].weight, &tree[i].left, &tree[i].right);
        total_weight += tree[i].weight;
    }
    
    dfs1(1);
    dfs2(1, 0);
    
    printf("%lld\n", min_distance);
    
    return 0;
}