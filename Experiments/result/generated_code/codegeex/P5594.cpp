#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    
    int a[1001][1001];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    int ans[1001] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[a[i][j]]++;
        }
    }
    
    for (int i = 1; i <= k; i++) {
        printf("%d ", ans[i]);
    }
    
    return 0;
}