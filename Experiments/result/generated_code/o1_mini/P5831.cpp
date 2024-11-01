#include <stdio.h>
#include <stdbool.h>

int main(){
    int K, N;
    scanf("%d %d", &K, &N);
    int pos[10][21];
    for(int k=0; k<K; k++){
        for(int i=0; i<N; i++){
            int num;
            scanf("%d", &num);
            pos[k][num] = i;
        }
    }
    int count = 0;
    for(int i=1; i<=N; i++){
        for(int j=i+1; j<=N; j++){
            bool consistent_i_before_j = true;
            bool consistent_j_before_i = true;
            for(int k=0; k<K; k++){
                if(pos[k][i] > pos[k][j]){
                    consistent_i_before_j = false;
                }
                if(pos[k][i] < pos[k][j]){
                    consistent_j_before_i = false;
                }
            }
            if(consistent_i_before_j || consistent_j_before_i){
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}