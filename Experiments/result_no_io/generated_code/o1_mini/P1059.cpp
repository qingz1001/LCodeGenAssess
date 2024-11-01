#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int N;
    scanf("%d", &N);
    int arr[100];
    for(int i=0;i<N;i++) scanf("%d", &arr[i]);
    qsort(arr, N, sizeof(int), cmp);
    int unique[100], M=0;
    if(N >0){
        unique[M++] = arr[0];
        for(int i=1;i<N;i++) {
            if(arr[i] != arr[i-1]) unique[M++] = arr[i];
        }
    }
    printf("%d\n", M);
    for(int i=0;i<M;i++) printf("%d%c", unique[i], i<M-1?' ':'\n');
    return 0;
}