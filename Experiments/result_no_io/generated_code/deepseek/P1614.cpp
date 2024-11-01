#include <stdio.h>
#include <limits.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int min_sum = INT_MAX;
    int current_sum = 0;
    
    // Calculate the sum of the first window
    for (int i = 0; i < m; i++) {
        current_sum += a[i];
    }
    min_sum = current_sum;
    
    // Slide the window across the array
    for (int i = m; i < n; i++) {
        current_sum += a[i] - a[i - m];
        if (current_sum < min_sum) {
            min_sum = current_sum;
        }
    }
    
    printf("%d\n", min_sum);
    
    return 0;
}