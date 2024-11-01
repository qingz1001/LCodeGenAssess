#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    long long b[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }
    
    int k, x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &k, &x, &y);
        x--; y--; // Convert to 0-based index
        if (k == 1) {
            b[x] -= b[y];
        } else if (k == 2) {
            b[x] /= b[y];
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%lld ", b[i]);
    }
    printf("\n");
    
    return 0;
}