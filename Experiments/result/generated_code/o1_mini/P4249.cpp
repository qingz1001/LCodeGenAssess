#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    int A[N][N];
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            scanf("%d", &A[i][j]);
        }
    }
    // Assign remaining matches to create a cyclic tournament
    for(int i=0;i<N;i++) {
        for(int j=i+1;j<N;j++) {
            if(A[i][j]==2){
                if( (j - i) <= N/2 ){
                    A[i][j] =1;
                    A[j][i] =0;
                }
                else{
                    A[i][j] =0;
                    A[j][i] =1;
                }
            }
        }
    }
    // Count cyclic triples
    long long count=0;
    for(int i=0;i<N;i++) {
        for(int j=i+1;j<N;j++) {
            for(int k=j+1;k<N;k++) {
                if( (A[i][j]==1 && A[j][k]==1 && A[k][i]==1) ||
                    (A[j][i]==1 && A[i][k]==1 && A[k][j]==1) ||
                    (A[i][j]==1 && A[j][k]==0 && A[k][i]==1) ||
                    (A[j][i]==1 && A[i][k]==0 && A[k][j]==1) ||
                    (A[i][j]==0 && A[j][k]==1 && A[k][i]==1) ||
                    (A[j][i]==0 && A[i][k]==1 && A[k][j]==1) ||
                    (A[i][j]==1 && A[j][k]==1 && A[k][i]==0) ||
                    (A[j][i]==1 && A[i][k]==1 && A[k][j]==0) ||
                    (A[i][j]==1 && A[j][k]==0 && A[k][i]==0) ||
                    (A[j][i]==1 && A[i][k]==0 && A[k][j]==0) ||
                    (A[i][j]==0 && A[j][k]==1 && A[k][i]==0) ||
                    (A[j][i]==0 && A[i][k]==1 && A[k][j]==0)
                  ){
                    // Check for cyclic
                    if( (A[i][j]==1 && A[j][k]==1 && A[k][i]==0) ||
                        (A[j][i]==1 && A[i][k]==1 && A[k][j]==0) ||
                        (A[i][j]==1 && A[j][k]==0 && A[k][i]==1) ||
                        (A[j][i]==0 && A[i][k]==1 && A[k][j]==1) ||
                        (A[i][j]==0 && A[j][k]==1 && A[k][i]==1) ||
                        (A[j][i]==1 && A[i][k]==0 && A[k][j]==1)
                      ){
                        count++;
                    }
                }
                // Alternatively, directly check cyclic
                if( (A[i][j]==1 && A[j][k]==1 && A[k][i]==1) ||
                    (A[j][i]==1 && A[i][k]==1 && A[k][j]==1) ){
                    // Do nothing, not cyclic
                }
                else{
                    // Check cyclic
                    if( (A[i][j]==1 && A[j][k]==1 && A[k][i]==1) ||
                        (A[j][i]==1 && A[i][k]==1 && A[k][j]==1) ){
                        // Not cyclic
                    }
                }
                // Proper cyclic check
                if( (A[i][j]==1 && A[j][k]==1 && A[k][i]==1)==0 &&
                    (A[j][i]==1 && A[i][k]==1 && A[k][j]==1)==0 ){
                    // Possible cyclic
                    if( (A[i][j]==1 && A[j][k]==1 && A[k][i]==1) ||
                        (A[j][i]==1 && A[i][k]==1 && A[k][j]==1) ){
                        // Not cyclic
                    }
                }
                // Proper cyclic check
                if( (A[i][j]==1 && A[j][k]==1 && A[k][i]==0) ||
                    (A[j][i]==1 && A[i][k]==1 && A[k][j]==0) ||
                    (A[i][j]==1 && A[j][k]==0 && A[k][i]==1) ||
                    (A[j][i]==0 && A[i][k]==1 && A[k][j]==1) ||
                    (A[i][j]==0 && A[j][k]==1 && A[k][i]==1) ||
                    (A[j][i]==1 && A[i][k]==0 && A[k][j]==1) ){
                    count++;
                }
            }
        }
    }
    printf("%lld\n", count);
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            if(j>0) printf(" ");
            printf("%d", A[i][j]);
        }
        printf("\n");
    }
}