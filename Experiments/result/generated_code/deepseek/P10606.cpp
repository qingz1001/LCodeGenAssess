#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    int min_cost = INT_MAX;
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (a[x] < min_cost) {
            min_cost = a[x];
        }
    }
    
    printf("%d\n", min_cost);
    
    free(a);
    return 0;
}