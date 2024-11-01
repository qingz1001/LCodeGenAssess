#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int opt;
        scanf("%d", &opt);
        
        if (opt == 1) {
            int l, r, K, D;
            scanf("%d %d %d %d", &l, &r, &K, &D);
            for (int j = l - 1; j < r; j++) {
                a[j] += K + (j - l + 1) * D;
            }
        } else if (opt == 2) {
            int p;
            scanf("%d", &p);
            printf("%d\n", a[p - 1]);
        }
    }
    
    return 0;
}