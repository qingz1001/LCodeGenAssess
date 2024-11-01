#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, M, P;
    scanf("%d %d %d", &N, &M, &P);
    
    // Allocate S and A matrices with 1-based indexing
    int **S = (int **)malloc((N+1) * sizeof(int *));
    int **A = (int **)malloc((N+1) * sizeof(int *));
    for(int i=0;i<=N;i++){
        S[i] = (int *)calloc((M+1), sizeof(int));
        A[i] = (int *)calloc((M+1), sizeof(int));
    }
    
    // Read S matrix
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            scanf("%d", &S[i][j]);
        }
    }
    
    // Compute A matrix
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            int sum = A[i-1][j] + A[i][j-1] + A[i-1][j-1];
            int tmp = S[i][j] - sum;
            int val = -1;
            for(int k=0; ;k++){
                int candidate = tmp + k * P;
                if(candidate >=0 && candidate < P){
                    val = candidate;
                    break;
                }
                if(k > 4) break; // Since P<=10 and S[i][j] <=36, k<=4 is sufficient
            }
            A[i][j] = val;
        }
    }
    
    // Print A matrix
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            if(j >1) printf(" ");
            printf("%d", A[i][j]);
        }
        printf("\n");
    }
    
    // Free memory
    for(int i=0;i<=N;i++){
        free(S[i]);
        free(A[i]);
    }
    free(S);
    free(A);
    
    return 0;
}