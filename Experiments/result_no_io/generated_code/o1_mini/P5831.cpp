#include <stdio.h>

int main(){
    int K, N;
    scanf("%d %d", &K, &N);
    int pos[K][N+1];
    for(int k=0; k<K; k++){
        for(int i=1; i<=N; i++){
            int cow;
            scanf("%d", &cow);
            pos[k][cow] = i;
        }
    }
    int count = 0;
    for(int a=1; a<=N; a++){
        for(int b=a+1; b<=N; b++){
            int a_before_b = 1, b_before_a = 1;
            for(int k=0; k<K; k++){
                if(pos[k][a] > pos[k][b]){
                    a_before_b = 0;
                }
                if(pos[k][b] > pos[k][a]){
                    b_before_a = 0;
                }
            }
            if(a_before_b || b_before_a){
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}