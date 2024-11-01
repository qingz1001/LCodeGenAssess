#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    if(N ==0){
        printf("0\n");
        return 0;
    }
    long *H = (long*)malloc(N * sizeof(long));
    for(int i=0;i<N;i++) scanf("%ld", &H[i]);
    int *left = (int*)malloc(N * sizeof(int));
    int *right = (int*)malloc(N * sizeof(int));
    left[0]=1;
    for(int i=1;i<N;i++){
        if(H[i] >= H[i-1]) left[i] = left[i-1]+1;
        else left[i]=1;
    }
    right[N-1]=1;
    for(int i=N-2;i>=0;i--){
        if(H[i] >= H[i+1]) right[i] = right[i+1]+1;
        else right[i]=1;
    }
    int max_width = 0;
    for(int i=0;i<N;i++){
        int width = left[i] + right[i] -1;
        if(width > max_width) max_width = width;
    }
    printf("%d\n", max_width);
    free(H);
    free(left);
    free(right);
    return 0;
}