#include <stdio.h>
#include <limits.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    if (m == 0) {
        printf("0\n");
        return 0;
    }
    
    int min_sum = INT_MAX;
    int current_sum = 0;
    
    for (int i = 0; i < n; i++) {
        current_sum += a[i];
        
        if (i >= m - 1) {
            min_sum = (min_sum < current_sum) ? min_sum : current_sum;
            current_sum -= a[i - m + 1];
        }
    }
    
    printf("%d\n", min_sum);
    
    return 0;
}