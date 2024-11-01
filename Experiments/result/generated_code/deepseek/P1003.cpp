#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int a[n], b[n], g[n], k[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &a[i], &b[i], &g[i], &k[i]);
    }
    
    int x, y;
    scanf("%d %d", &x, &y);
    
    int result = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (x >= a[i] && x <= a[i] + g[i] && y >= b[i] && y <= b[i] + k[i]) {
            result = i + 1;
            break;
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}