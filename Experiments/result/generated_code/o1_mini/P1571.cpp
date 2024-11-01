#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    if(n == 0 || m == 0){
        return 0;
    }
    int* A = (int*)malloc(n * sizeof(int));
    int* B = (int*)malloc(m * sizeof(int));
    for(int i = 0; i < n; i++) scanf("%d", &A[i]);
    for(int i = 0; i < m; i++) scanf("%d", &B[i]);
    qsort(B, m, sizeof(int), cmp);
    int first = 1;
    for(int i = 0; i < n; i++){
        if(bsearch(&A[i], B, m, sizeof(int), cmp) != NULL){
            if(first){
                printf("%d", A[i]);
                first = 0;
            }
            else{
                printf(" %d", A[i]);
            }
        }
    }
    free(A);
    free(B);
    return 0;
}