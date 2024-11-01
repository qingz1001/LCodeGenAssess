#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int awards1[MAX_N], awards2[MAX_N];
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &awards1[i]);
    }
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &awards2[i]);
    }
    
    qsort(awards2, m, sizeof(int), compare);
    
    for (int i = 0; i < n; i++) {
        if (bsearch(&awards1[i], awards2, m, sizeof(int), compare) != NULL) {
            printf("%d ", awards1[i]);
        }
    }
    
    printf("\n");
    
    return 0;
}