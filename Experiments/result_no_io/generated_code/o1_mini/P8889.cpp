#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Comparator for qsort and bsearch
int cmpfunc(const void *a, const void *b) {
    if (*(int64_t*)a < *(int64_t*)b) return -1;
    if (*(int64_t*)a > *(int64_t*)b) return 1;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Allocate memory for a and b
    int64_t *a = (int64_t*) malloc(n * sizeof(int64_t));
    int64_t *b = (int64_t*) malloc(m * sizeof(int64_t));
    
    // Read a
    for(int i=0;i<n;i++){
        scanf("%lld", &a[i]);
    }
    
    // Read b
    for(int i=0;i<m;i++){
        scanf("%lld", &b[i]);
    }
    
    // Sort b
    qsort(b, m, sizeof(int64_t), cmpfunc);
    
    // Iterate a and count segments
    int count = 0;
    int in_segment = 0;
    for(int i=0;i<n;i++){
        // Binary search a[i] in b
        if (bsearch(&a[i], b, m, sizeof(int64_t), cmpfunc) != NULL){
            in_segment = 0;
        }
        else{
            if(!in_segment){
                count++;
                in_segment = 1;
            }
        }
    }
    
    printf("%d\n", count);
    
    // Free memory
    free(a);
    free(b);
    
    return 0;
}