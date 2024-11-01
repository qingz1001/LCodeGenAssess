#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b){
    int x = *((int*)a);
    int y = *((int*)b);
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int main(){
    int n;
    double k;
    scanf("%d %lf", &n, &k);
    int* d = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &d[i]);
    qsort(d, n, sizeof(int), compare);
    for(int i=0;i<n;i++){
        if(i>0) printf(" ");
        printf("%d", d[i]);
    }
    printf("\n");
    free(d);
    return 0;
}