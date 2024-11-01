#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 151

int N, P;
int tree[MAX_N][MAX_N];
int size[MAX_N];
int result = 0;

void dfs(int node, int parent) {
    size[node] = 1;
    for (int i = 1; i <= N; i++) {
        if (i != parent && tree[node][i]) {
            dfs(i, node);
            size[node] += size[i];
            if (size[i] == P || size[i] == N - P) {
                result++;
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &P);
    
    memset(tree, 0, sizeof(tree));
    
    for (int i = 1; i < N; i++) {
        int parent, child;
        scanf("%d %d", &parent, &child);
        tree[parent][child] = tree[child][parent] = 1;
    }
    
    dfs(1, 0);
    
    printf("%d\n", result);
    
    return 0;
}