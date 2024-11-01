#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[3001];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    int min_sum = 0;
    for (int i = 1; i <= m; i++) {
        min_sum += a[i];
    }
    
    int current_sum = min_sum;
    for (int i = m + 1; i <= n; i++) {
        current_sum = current_sum - a[i - m] + a[i];
        if (current_sum < min_sum) {
            min_sum = current_sum;
        }
    }
    
    printf("%d\n", min_sum);
    
    return 0;
}