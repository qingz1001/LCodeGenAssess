#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] + b[i] >= n - 1) {
            total++;
        }
    }
    
    printf("%d\n", total);
    
    free(a);
    free(b);
    
    return 0;
}