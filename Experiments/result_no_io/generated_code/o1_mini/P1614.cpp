#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    if (m == 0) {
        printf("0\n");
        return 0;
    }
    
    int *a = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    long long current_sum = 0;
    for(int i = 0; i < m; i++) {
        current_sum += a[i];
    }
    
    long long min_sum = current_sum;
    
    for(int i = m; i < n; i++) {
        current_sum += a[i] - a[i - m];
        if(current_sum < min_sum) {
            min_sum = current_sum;
        }
    }
    
    printf("%lld\n", min_sum);
    free(a);
    return 0;
}