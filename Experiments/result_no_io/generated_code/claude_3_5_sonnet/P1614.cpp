#include <stdio.h>
#include <limits.h>

#define MAX_N 3000

int main() {
    int n, m;
    int a[MAX_N];
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    if (m == 0) {
        printf("0\n");
        return 0;
    }
    
    int sum = 0;
    for (int i = 0; i < m; i++) {
        sum += a[i];
    }
    
    int min_sum = sum;
    
    for (int i = m; i < n; i++) {
        sum = sum - a[i-m] + a[i];
        if (sum < min_sum) {
            min_sum = sum;
        }
    }
    
    printf("%d\n", min_sum);
    
    return 0;
}