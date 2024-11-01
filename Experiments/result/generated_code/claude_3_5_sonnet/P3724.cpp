#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 20

int n, m, mc;
int a[MAX_N + 1], w[MAX_N + 1];
int C[MAX_M + 1];

int dfs(int day, int confidence, int boss_confidence, int level, int sarcasm, int attack_count) {
    if (confidence < 0) return 0;
    if (boss_confidence == 0) return 1;
    if (day > n || boss_confidence < 0) return 0;
    
    confidence -= a[day];
    if (confidence < 0) return 0;
    
    // Option 1: Reply
    if (dfs(day + 1, confidence, boss_confidence - 1, level, sarcasm, attack_count)) return 1;
    
    // Option 2: Solve problems
    if (dfs(day + 1, confidence + w[day] > mc ? mc : confidence + w[day], boss_confidence, level, sarcasm, attack_count)) return 1;
    
    // Option 3: Increase level
    if (dfs(day + 1, confidence, boss_confidence, level + 1, sarcasm, attack_count)) return 1;
    
    // Option 4: Increase sarcasm
    if (dfs(day + 1, confidence, boss_confidence, level, sarcasm * level, attack_count)) return 1;
    
    // Option 5: Attack boss
    if (attack_count < 2) {
        int new_boss_confidence = boss_confidence - sarcasm;
        if (new_boss_confidence >= 0 && dfs(day + 1, confidence, new_boss_confidence, 0, 1, attack_count + 1)) return 1;
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
    
    for (int i = 1; i <= m; i++) {
        scanf("%d", &C[i]);
    }
    
    for (int i = 1; i <= m; i++) {
        int result = dfs(1, mc, C[i], 0, 1, 0);
        printf("%d\n", result);
    }
    
    return 0;
}