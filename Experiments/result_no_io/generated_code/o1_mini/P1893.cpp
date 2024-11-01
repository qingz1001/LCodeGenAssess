#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    if(N <=0){
        printf("0");
        return 0;
    }
    long long *H = (long long *)malloc(N * sizeof(long long));
    for(int i=0;i<N;i++) scanf("%lld", &H[i]);

    int *left = (int *)malloc(N * sizeof(int));
    int *right = (int *)malloc(N * sizeof(int));

    left[0] = 1;
    for(int i=1;i<N;i++){
        if(H[i] >= H[i-1]) left[i] = left[i-1] +1;
        else left[i] =1;
    }

    right[N-1]=1;
    for(int i=N-2;i>=0;i--){
        if(H[i] >= H[i+1]) right[i] = right[i+1] +1;
        else right[i] =1;
    }

    int max_width = 1;
    for(int i=0;i<N;i++){
        int current = left[i] + right[i] -1;
        if(current > max_width) max_width = current;
    }

    free(H);
    free(left);
    free(right);
    printf("%d", max_width);
    return 0;
}