#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void *a, const void *b) {
    long long int aa = *(long long int*)a;
    long long int bb = *(long long int*)b;
    if (aa < bb) return -1;
    if (aa > bb) return 1;
    return 0;
}

int main(){
    int N;
    if (scanf("%d", &N)!=1){
        return 1;
    }
    long long int *S = (long long int*)malloc(N * sizeof(long long int));
    for(int i=0;i<N;i++){
        if(scanf("%lld", &S[i])!=1){
            free(S);
            return 1;
        }
    }
    qsort(S, N, sizeof(long long int), compare);
    if(N ==1){
        printf("1\n");
        free(S);
        return 0;
    }
    // Find max_diff
    long long int max_diff = S[N-1] - S[0];
    // Allocate difference array
    // To save memory, use byte array
    bool *diff = (bool*)calloc(max_diff +1, sizeof(bool));
    // Compute differences
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            long long int d = S[j] - S[i];
            if(d >=1 && d <= max_diff){
                diff[d] = true;
            }
        }
    }
    free(S);
    // Iterate K from 1 upward
    // If N ==1, K=1 is already handled
    // Else, start K from 2
    long long int K_start = 2;
    // Find minimal K
    for(long long int K = K_start; K <= max_diff +1; K++){
        bool valid = true;
        for(long long int m = K; m <= max_diff; m += K){
            if(diff[m]){
                valid = false;
                break;
            }
        }
        if(valid){
            printf("%lld\n", K);
            free(diff);
            return 0;
        }
    }
    // If not found in loop, K = max_diff +1
    printf("%lld\n", max_diff +1);
    free(diff);
    return 0;
}