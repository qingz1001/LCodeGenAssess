#include <stdio.h>
#include <limits.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[200005];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    int min_cost = INT_MAX;
    
    for (int i = 1; i <= n; i++) {
        int current_cost = 0;
        for (int j = 1; j <= m; j++) {
            int x, y;
            scanf("%d %d", &x, &y);
            if (x < y) {
                // Swap x and y to ensure x > y
                int temp = x;
                x = y;
                y = temp;
            }
            // Calculate the cost to satisfy the condition from y to x
            if (x == i) {
                current_cost += a[y];
            } else if (y == i) {
                current_cost += a[x];
            } else {
                // If i is not on the path from y to x, it is impossible to satisfy the condition
                current_cost = INT_MAX;
                break;
            }
        }
        if (current_cost < min_cost) {
            min_cost = current_cost;
        }
    }
    
    printf("%d\n", min_cost);
    return 0;
}