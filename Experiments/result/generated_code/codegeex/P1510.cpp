#include <stdio.h>

int main() {
    int v, n, c;
    scanf("%d%d%d", &v, &n, &c);
    
    int k[10005], m[10005];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &k[i], &m[i]);
    }
    
    // 动态规划数组，f[j] 表示填海体积为 j 时需要的最小体力
    int f[10005] = {0};
    for (int i = 1; i <= v; i++) {
        f[i] = 1000000000; // 初始化为一个很大的值
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = v; j >= k[i]; j--) {
            if (f[j - k[i]] + m[i] < f[j]) {
                f[j] = f[j - k[i]] + m[i];
            }
        }
    }
    
    if (f[v] <= c) {
        printf("%d\n", c - f[v]);
    } else {
        printf("Impossible\n");
    }
    
    return 0;
}