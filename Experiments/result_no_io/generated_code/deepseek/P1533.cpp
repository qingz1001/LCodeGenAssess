#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int q = 0; q < m; q++) {
        int i, j, k;
        scanf("%d %d %d", &i, &j, &k);
        
        int *subarray = (int *)malloc((j - i + 1) * sizeof(int));
        for (int x = i - 1; x < j; x++) {
            subarray[x - i + 1] = a[x];
        }
        
        qsort(subarray, j - i + 1, sizeof(int), compare);
        
        printf("%d\n", subarray[k - 1]);
        
        free(subarray);
    }
    
    free(a);
    return 0;
}