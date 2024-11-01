#include <stdio.h>

int main() {
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);
    
    int a[1001];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int total_cost = 0;
    for (int i = 0; i < n; i++) {
        if (x * a[i] <= y) {
            total_cost += x * a[i];
        } else {
            total_cost += y;
        }
    }
    
    printf("%d\n", total_cost);
    return 0;
}