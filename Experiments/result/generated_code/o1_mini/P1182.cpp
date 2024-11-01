#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int *A = (int*)malloc(N * sizeof(int));
    int max = 0;
    long long sum = 0;
    for(int i=0;i<N;i++){
        scanf("%d", &A[i]);
        if(A[i] > max) max = A[i];
        sum += A[i];
    }
    long long low = max;
    long long high = sum;
    while(low < high){
        long long mid = low + (high - low) / 2;
        int count = 1;
        long long current = 0;
        for(int i=0;i<N;i++){
            if(current + A[i] > mid){
                count++;
                current = A[i];
            }
            else{
                current += A[i];
            }
        }
        if(count <= M){
            high = mid;
        }
        else{
            low = mid +1;
        }
    }
    printf("%lld\n", low);
    free(A);
    return 0;
}