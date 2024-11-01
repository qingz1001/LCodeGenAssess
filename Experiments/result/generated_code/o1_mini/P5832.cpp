#include <stdio.h>
#include <string.h>

int main(){
    int N;
    scanf("%d", &N);
    char S[101];
    scanf("%s", S);
    int K;
    for(K=1; K<=N; K++){
        int unique = 1;
        for(int i=0; i + K <= N && unique; i++){
            for(int j=i+1; j + K <= N && unique; j++){
                if(strncmp(&S[i], &S[j], K) == 0){
                    unique = 0;
                }
            }
        }
        if(unique){
            printf("%d\n", K);
            return 0;
        }
    }
    printf("%d\n", N);
    return 0;
}