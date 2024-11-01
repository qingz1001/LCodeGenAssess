#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    long long b[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &b[i]);
    }
    
    int operations[m][3];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &operations[i][0], &operations[i][1], &operations[i][2]);
    }
    
    // Reverse the operations
    for (int i = m - 1; i >= 0; i--) {
        int k = operations[i][0];
        int x = operations[i][1] - 1;
        int y = operations[i][2] - 1;
        
        if (k == 1) {
            b[x] -= b[y];
        } else if (k == 2) {
            if (x == y) {
                b[x] = b[x] / 2;
            } else {
                b[x] = b[x] / b[y];
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%lld ", b[i]);
    }
    
    return 0;
}