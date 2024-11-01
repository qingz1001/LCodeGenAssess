#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int *delta = (int *)calloc(n + 1, sizeof(int));
    
    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d", &op);
        
        if (op == 1) {
            scanf("%d %d", &x, &y);
            delta[x - 1] += y;
            delta[n] -= y;
        } else if (op == 2) {
            scanf("%d", &x);
            int sum = 0;
            for (int j = 0; j < x; j++) {
                sum += delta[j];
            }
            printf("%d\n", a[x - 1] + sum);
        }
    }
    
    free(a);
    free(delta);
    
    return 0;
}