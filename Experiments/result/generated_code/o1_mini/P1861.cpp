#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    int Ini[MAX][MAX];
    int Fin[MAX][MAX];
    int D[MAX][MAX];
    
    // Read Ini
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d", &Ini[i][j]);
        }
    }
    
    // Read until a blank line
    int c;
    while((c = getchar()) != EOF && c != '\n');
    
    // Read Fin
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d", &Fin[i][j]);
        }
    }
    
    // Compute D
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            D[i][j] = Ini[i][j] - Fin[i][j];
        }
    }
    
    int total_magic = 0;
    int max_k = (N > M ? N : M) -2;
    for(int k = (N > M ? N : M)-2; k >=1; k--){
        // Rows
        if( (k+1) %2 ==0 ){
            for(int i=0;i<N;i++){
                for(int j1=0; j1 +k+1 < M; j1++){
                    int j2 = j1 +k +1;
                    int center = j1 + (k +1)/2;
                    if(D[i][j1] >0 && D[i][j2]>0 && D[i][center] <0){
                        int t = D[i][j1];
                        if(t > D[i][j2]) t = D[i][j2];
                        if(t > -D[i][center]) t = -D[i][center];
                        if(t >0){
                            D[i][j1] -= t;
                            D[i][j2] -= t;
                            D[i][center] += t;
                            total_magic += t *k;
                        }
                    }
                }
            }
        }
        
        // Columns
        if( (k+1) %2 ==0 ){
            for(int j=0;j<M;j++){
                for(int i1=0; i1 +k+1 < N; i1++){
                    int i2 = i1 +k +1;
                    int center = i1 + (k +1)/2;
                    if(D[i1][j] >0 && D[i2][j]>0 && D[center][j] <0){
                        int t = D[i1][j];
                        if(t > D[i2][j]) t = D[i2][j];
                        if(t > -D[center][j]) t = -D[center][j];
                        if(t >0){
                            D[i1][j] -= t;
                            D[i2][j] -= t;
                            D[center][j] += t;
                            total_magic += t *k;
                        }
                    }
                }
            }
        }
    }
    
    printf("%d\n", total_magic);
    return 0;
}