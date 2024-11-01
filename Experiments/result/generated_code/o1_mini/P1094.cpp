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
    int w, n;
    scanf("%d", &w);
    scanf("%d", &n);
    int *P = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &P[i]);
    qsort(P, n, sizeof(int), cmp);
    int i_ptr=0, j_ptr=n-1, groups=0;
    while(i_ptr <= j_ptr){
        if(P[i_ptr] + P[j_ptr] <=w){
            i_ptr++;
        }
        groups++;
        j_ptr--;
    }
    printf("%d\n", groups);
    free(P);
    return 0;
}