#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int main(){
    int N;
    scanf("%d", &N);
    int adj[MAX][MAX];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            scanf("%d", &adj[i][j]);
        }
    }
    // Assign undecided edges
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            if(adj[i][j]==2){
                int count1=0, count0=0;
                for(int k=0;k<N;k++){
                    if(k == i || k == j) continue;
                    if(adj[j][k]==1 && adj[k][i]==1){
                        count1++;
                    }
                    if(adj[i][k]==1 && adj[k][j]==1){
                        count0++;
                    }
                }
                if(count1 >= count0){
                    adj[i][j]=1;
                    adj[j][i]=0;
                }
                else{
                    adj[i][j]=0;
                    adj[j][i]=1;
                }
            }
        }
    }
    // Count cyclic triples
    long long count =0;
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            for(int k=j+1;k<N;k++){
                // Check i->j, j->k, k->i
                if(adj[i][j]==1 && adj[j][k]==1 && adj[k][i]==1){
                    count++;
                }
                // Check i->k, k->j, j->i
                if(adj[i][k]==1 && adj[k][j]==1 && adj[j][i]==1){
                    count++;
                }
                // Check j->i, i->k, k->j
                if(adj[j][i]==1 && adj[i][k]==1 && adj[k][j]==1){
                    count++;
                }
            }
        }
    }
    printf("%lld\n", count);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i == j){
                printf("0");
            }
            else{
                printf("%d", adj[i][j]);
            }
            if(j != N-1){
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}