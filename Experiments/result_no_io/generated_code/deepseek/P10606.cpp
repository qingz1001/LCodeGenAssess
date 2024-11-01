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
    
    int *min_cost = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        min_cost[i] = INT_MAX;
    }
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (a[x] < min_cost[y]) {
            min_cost[y] = a[x];
        }
    }
    
    int total_cost = 0;
    for (int i = 1; i <= n; i++) {
        if (min_cost[i] != INT_MAX) {
            total_cost += min_cost[i];
        }
    }
    
    printf("%d\n", total_cost);
    
    free(a);
    free(min_cost);
    
    return 0;
}