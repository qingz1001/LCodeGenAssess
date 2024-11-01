#include <stdio.h>

int main() {
    int n, v, m, a;
    scanf("%d %d %d %d", &n, &v, &m, &a);
    
    int total_revenue = 0;
    for (int i = 1; i <= n; ++i) {
        total_revenue += v + (i - 1) / m * a;
    }
    
    printf("%d\n", total_revenue);
    
    return 0;
}