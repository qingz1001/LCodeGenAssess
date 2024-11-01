#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int w, n;
    scanf("%d", &w);
    scanf("%d", &n);
    int P[30000];
    for(int i=0; i<n; i++){
        scanf("%d", &P[i]);
    }
    qsort(P, n, sizeof(int), cmp);
    int groups = 0;
    int i = 0, j = n-1;
    while(i <= j){
        if(P[i] + P[j] <= w){
            i++;
        }
        j--;
        groups++;
    }
    printf("%d\n", groups);
    return 0;
}