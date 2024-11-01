#include <stdio.h>
#include <stdlib.h>

#define MAX_N 151

int n, p;
int tree[MAX_N][MAX_N];
int size[MAX_N];
int count = 0;

void dfs(int node, int parent) {
    size[node] = 1;
    for (int i = 1; i <= n; i++) {
        if (tree[node][i] && i != parent) {
            dfs(i, node);
            size[node] += size[i];
            if (size[i] == p || size[i] == n - p) {
                count++;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    
    for (int i = 1; i < n; i++) {
        int parent, child;
        scanf("%d %d", &parent, &child);
        tree[parent][child] = tree[child][parent] = 1;
    }
    
    dfs(1, 0);
    
    printf("%d\n", count);
    
    return 0;
}