#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[3001];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int sum = 0;
    for (int i = 0; i < m; i++) {
        sum += a[i];
    }
    int min_sum = sum;
    
    for (int i = m; i < n; i++) {
        sum = sum - a[i - m] + a[i];
        if (sum < min_sum) {
            min_sum = sum;
        }
    }
    
    printf("%d\n", min_sum);
    
    return 0;
}