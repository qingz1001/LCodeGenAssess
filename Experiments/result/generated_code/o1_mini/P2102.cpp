#include <stdio.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=1;i<=N;i++){
        if(i < N){
            for(int j=0;j<M;j++) printf("A");
        }
        else{
            for(int j=1;j<=M;j++){
                if(j%2 == 1) printf("B");
                else printf("C");
            }
        }
        printf("\n");
    }
    return 0;
}