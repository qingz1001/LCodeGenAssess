#include <stdio.h>

int main() {
    int k, m, n;
    scanf("%d %d %d", &k, &m, &n);
    
    int a[m], b[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    
    int found = 0;
    for (int i = 0; i < m; i++) {
        if (a[i] == 0 && b[i] > 0) {
            printf("%d ", i + 1);
            found = 1;
        } else if (a[i] != 0 && b[i] * k / a[i] >= n) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    
    if (!found) {
        printf("-1");
    }
    
    return 0;
}