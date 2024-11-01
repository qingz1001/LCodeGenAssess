#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 20

int n, m, mc;
int a[MAX_N + 1], w[MAX_N + 1];
int C[MAX_M];

int dfs(int day, int confidence, int level, int sarcasm, int attack_count, int target) {
    if (day > n) return confidence >= 0 && target == 0;
    if (confidence < 0 || target < 0) return 0;
    
    confidence -= a[day];
    if (confidence < 0) return 0;
    
    // Option 1: Talk back
    if (dfs(day + 1, confidence, level, sarcasm, attack_count, target - 1)) return 1;
    
    // Option 2: Do easy problems
    if (dfs(day + 1, confidence + w[day] > mc ? mc : confidence + w[day], level, sarcasm, attack_count, target)) return 1;
    
    // Option 3: Increase level
    if (dfs(day + 1, confidence, level + 1, sarcasm, attack_count, target)) return 1;
    
    // Option 4: Increase sarcasm
    if (dfs(day + 1, confidence, level, sarcasm * level, attack_count, target)) return 1;
    
    // Option 5: Attack the boss (if possible)
    if (attack_count < 2 && target >= sarcasm) {
        if (dfs(day + 1, confidence, 0, 1, attack_count + 1, target - sarcasm)) return 1;
    }
    
    return 0;
}

int main() {
    scanf("%d %d %d", &n, &m, &mc);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &C[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int result = dfs(1, mc, 0, 1, 0, C[i]);
        printf("%d\n", result);
    }
    
    return 0;
}