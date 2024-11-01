#include <stdio.h>
#include <string.h>

#define MAX_V 25
#define MAX_G 15

int v, g;
int required[MAX_V];
int feeds[MAX_G][MAX_V];
int best_count = MAX_G + 1;
int best_combination[MAX_G];
int current_combination[MAX_G];

void dfs(int index, int count, int current[]) {
    if (count >= best_count) return;
    
    int satisfied = 1;
    for (int i = 0; i < v; i++) {
        if (current[i] < required[i]) {
            satisfied = 0;
            break;
        }
    }
    
    if (satisfied) {
        best_count = count;
        memcpy(best_combination, current_combination, sizeof(int) * MAX_G);
        return;
    }
    
    if (index == g) return;
    
    // 不选择当前饲料
    dfs(index + 1, count, current);
    
    // 选择当前饲料
    for (int i = 0; i < v; i++) {
        current[i] += feeds[index][i];
    }
    current_combination[count] = index + 1;
    dfs(index + 1, count + 1, current);
    for (int i = 0; i < v; i++) {
        current[i] -= feeds[index][i];
    }
}

int main() {
    scanf("%d", &v);
    for (int i = 0; i < v; i++) {
        scanf("%d", &required[i]);
    }
    
    scanf("%d", &g);
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &feeds[i][j]);
        }
    }
    
    int current[MAX_V] = {0};
    dfs(0, 0, current);
    
    printf("%d", best_count);
    for (int i = 0; i < best_count; i++) {
        printf(" %d", best_combination[i]);
    }
    printf("\n");
    
    return 0;
}