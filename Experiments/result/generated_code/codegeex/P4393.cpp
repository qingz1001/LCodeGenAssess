#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long *a = (long long *)malloc(n * sizeof(long long));
    long long *cost = (long long *)malloc(n * sizeof(long long));
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    
    long long total_cost = 0;
    for (int i = 0; i < n - 1; i++) {
        cost[i] = (a[i] > a[i+1]) ? a[i+1] : a[i];
        total_cost += cost[i];
    }
    
    printf("%lld\n", total_cost);
    
    free(a);
    free(cost);
    
    return 0;
}