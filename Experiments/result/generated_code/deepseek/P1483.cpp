#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int *)malloc(n * sizeof(int));
    int *delta = (int *)calloc(n + 1, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 0; i < m; i++) {
        int op, x, y, j;
        scanf("%d", &op);
        
        if (op == 1) {
            scanf("%d %d", &x, &y);
            delta[x - 1] += y;
        } else if (op == 2) {
            scanf("%d", &j);
            int sum = a[j - 1];
            for (int k = 1; k * x <= n; k++) {
                sum += delta[k * x - 1];
            }
            printf("%d\n", sum);
        }
    }
    
    free(a);
    free(delta);
    
    return 0;
}