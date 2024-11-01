#include <stdio.h>
#include <limits.h>

#define MAX_N 200000

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n;
    int a[MAX_N];
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int max_sum = INT_MIN;
    int current_sum = 0;
    
    for (int i = 0; i < n; i++) {
        current_sum = max(a[i], current_sum + a[i]);
        max_sum = max(max_sum, current_sum);
    }
    
    printf("%d\n", max_sum);
    
    return 0;
}