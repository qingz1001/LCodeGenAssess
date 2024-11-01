#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001

int N;
int superior[MAX_N];
int subordinates[MAX_N][MAX_N];
int sub_count[MAX_N];
int depth[MAX_N];
int max_depth = 0;

void dfs(int node, int d) {
    depth[node] = d;
    if (d > max_depth) max_depth = d;
    
    for (int i = 0; i < sub_count[node]; i++) {
        dfs(subordinates[node][i], d + 1);
    }
}

int main() {
    scanf("%d", &N);
    
    memset(sub_count, 0, sizeof(sub_count));
    
    for (int i = 2; i <= N; i++) {
        int sup;
        scanf("%d", &sup);
        superior[i] = sup;
        subordinates[sup][sub_count[sup]++] = i;
    }
    
    dfs(1, 0);
    
    printf("%d\n", max_depth);
    
    for (int i = 1; i <= N; i++) {
        int max_sub_depth = 0;
        for (int j = 0; j < sub_count[i]; j++) {
            if (depth[subordinates[i][j]] > max_sub_depth) {
                max_sub_depth = depth[subordinates[i][j]];
            }
        }
        
        if (max_depth == max_sub_depth + depth[i]) {
            printf("%d ", i);
        }
    }
    
    printf("\n");
    
    return 0;
}