#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }
    
    int count_a0 = 0, count_a1 = 0;
    int count_b0 = 0, count_b1 = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) count_a0++;
        else count_a1++;
        
        if (b[i] == 0) count_b0++;
        else count_b1++;
    }
    
    int flips_needed = min(abs(count_a0 - count_b0), abs(count_a1 - count_b1));
    
    printf("%d\n", flips_needed);
    
    free(a);
    free(b);
    
    return 0;
}