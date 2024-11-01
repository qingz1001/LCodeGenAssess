#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *x = (int *)malloc(n * sizeof(int));
    int *y = (int *)malloc(n * sizeof(int));
    
    int min_y = 10000;
    int max_y = -10000;
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
        if (y[i] < min_y) {
            min_y = y[i];
        }
        if (y[i] > max_y) {
            max_y = y[i];
        }
    }
    
    int total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += abs(y[i] - (min_y + max_y) / 2);
    }
    
    printf("%d\n", total_length);
    
    free(x);
    free(y);
    
    return 0;
}