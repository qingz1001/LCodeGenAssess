#include <stdio.h>

int main() {
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    
    int T[100005];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &T[i]);
    }
    
    int lastAns = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        
        if (p == 1) {
            x ^= lastAns;
            y ^= lastAns;
        }
        
        T[x] = y;
        
        // 计算最优策略下的答案
        int ans = 0;
        for (int j = 1; j <= n; j++) {
            ans = ans + T[j];
        }
        
        printf("%d\n", ans);
        lastAns = ans;
    }
    
    return 0;
}