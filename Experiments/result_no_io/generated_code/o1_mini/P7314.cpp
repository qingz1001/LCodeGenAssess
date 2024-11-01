#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    int *A = (int*) malloc(N * sizeof(int));
    for(int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    int min_diff = 2147483647;
    for(int i = 0; i < N - 1; i++) {
        int diff = abs(A[i] - A[i + 1]);
        if(diff < min_diff){
            min_diff = diff;
        }
    }
    printf("%d", min_diff);
    free(A);
    return 0;
}