#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);
    
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int min_cost = INT_MAX;
    for (int i = 0; i <= n; i++) {
        int cost = i * y;
        for (int j = 0; j < n; j++) {
            if (j >= i) {
                cost += a[j];
            } else {
                cost += a[j] * x;
            }
        }
        if (cost < min_cost) {
            min_cost = cost;
        }
    }
    
    printf("%d\n", min_cost);
    
    free(a);
    return 0;
}