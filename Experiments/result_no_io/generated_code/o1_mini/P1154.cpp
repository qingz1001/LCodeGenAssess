#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    int *S = (int*)malloc(N * sizeof(int));
    int max_S = 0;
    for(int i=0;i<N;i++){
        scanf("%d", &S[i]);
        if(S[i] > max_S) max_S = S[i];
    }
    int max_K = max_S +1;
    int *last_used = (int*)calloc(max_K +1, sizeof(int));
    for(int K=N; K<=max_K; K++){
        int flag = 1;
        for(int i=0;i<N;i++){
            int mod = S[i] % K;
            if(last_used[mod] == K){
                flag =0;
                break;
            }
            last_used[mod] = K;
        }
        if(flag){
            printf("%d", K);
            free(S);
            free(last_used);
            return 0;
        }
    }
    // As per problem statement, K always exists
    free(S);
    free(last_used);
    return 0;
}