#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int *min_values = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int start = (i - m >= 0) ? (i - m) : 0;
        int min_val = a[start];
        for (int j = start + 1; j <= i; j++) {
            if (a[j] < min_val) {
                min_val = a[j];
            }
        }
        min_values[i] = (i == 0) ? 0 : min_val;
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d\n", min_values[i]);
    }
    
    free(a);
    free(min_values);
    
    return 0;
}