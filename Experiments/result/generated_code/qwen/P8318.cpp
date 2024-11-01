#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    long long b[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }
    
    while (m--) {
        int k, x, y;
        scanf("%d %d %d", &k, &x, &y);
        if (k == 1) {
            b[x - 1] += b[y - 1];
        } else {
            b[x - 1] *= b[y - 1];
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%lld ", b[i]);
    }
    return 0;
}