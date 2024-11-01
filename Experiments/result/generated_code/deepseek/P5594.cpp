#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int **a = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    int *days = (int *)calloc(k + 1, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            days[a[i][j]]++;
        }
    }
    
    for (int i = 1; i <= k; i++) {
        printf("%d ", days[i]);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    free(days);
    
    return 0;
}