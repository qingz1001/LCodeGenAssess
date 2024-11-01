#include <stdio.h>
#include <stdlib.h>

int main(){
    int M, P;
    scanf("%d %d", &M, &P);
    long long A;
    int O, S, U;
    scanf("%lld", &A);
    scanf("%d", &O);
    scanf("%d", &S);
    scanf("%d", &U);
    
    if(M ==0){
        printf("0\n");
        return 0;
    }
    
    // Initialize F[x] = (O*x*x + S*x + U) mod P
    int *F = (int*)calloc(M+1, sizeof(int));
    for(int x=1; x<=M; x++){
        long long tmp = (long long)O * x * x + (long long)S * x + U;
        F[x] = tmp % P;
    }
    
    // Determine k' = min(A, M)
    int k_prime;
    if(A < M){
        k_prime = A;
    }
    else{
        k_prime = M;
    }
    
    // Initialize dp_prev and current_dp
    unsigned char *dp_prev = (unsigned char*)calloc(M+1, sizeof(unsigned char));
    unsigned char *current_dp = (unsigned char*)calloc(M+1, sizeof(unsigned char));
    
    // For k=1
    for(int m=1; m<=M; m++){
        dp_prev[m] = F[m] % P;
    }
    
    int S_total = dp_prev[M] % P;
    
    // Iterate over k from 2 to k_prime
    for(int k=2; k<=k_prime; k++){
        for(int m=1; m<=M; m++){
            unsigned int sum = 0;
            for(int x=1; x<=m; x++){
                sum += (unsigned int)F[x] * dp_prev[m -x];
                if(sum >= P){
                    sum -= P;
                }
            }
            current_dp[m] = sum % P;
        }
        // Add current_dp[M] to S_total
        S_total = (S_total + current_dp[M]) % P;
        // Swap dp_prev and current_dp
        unsigned char *temp = dp_prev;
        dp_prev = current_dp;
        current_dp = temp;
    }
    
    printf("%d\n", S_total);
    
    free(F);
    free(dp_prev);
    free(current_dp);
    return 0;
}