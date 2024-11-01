#include <stdio.h>

#define MAXN 100005

int c[5], d[5], s;
int f[MAXN];

int main() {
    int n;
    scanf("%d%d%d%d%d", &c[1], &c[2], &c[3], &c[4], &n);
    
    while (n--) {
        int ans = 0;
        for (int i = 1; i <= 4; i++) {
            scanf("%d", &d[i]);
        }
        scanf("%d", &s);
        
        // 初始化f数组
        for (int i = 0; i <= s; i++) {
            f[i] = 0;
        }
        f[0] = 1;
        
        // 动态规划求解
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j <= s; j++) {
                for (int k = 0; k <= d[i]; k++) {
                    if (j >= k * c[i]) {
                        f[j] += f[j - k * c[i]];
                    }
                }
            }
        }
        
        // 计算答案
        for (int i = 0; i <= s; i++) {
            if (i % c[1] == 0 && i % c[2] == 0 && i % c[3] == 0 && i % c[4] == 0) {
                ans += f[i];
            }
        }
        
        printf("%d\n", ans);
    }
    
    return 0;
}