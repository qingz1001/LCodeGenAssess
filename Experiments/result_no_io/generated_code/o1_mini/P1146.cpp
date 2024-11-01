#include<stdio.h>
#include<stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    int *state = (int*)calloc(N, sizeof(int));
    printf("%d\n", N);
    for(int i=0;i<N;i++){
        // Flip all except i
        for(int j=0;j<N;j++){
            if(j != i){
                state[j] = state[j] ^ 1;
            }
        }
        // Print current state
        for(int j=0;j<N;j++){
            printf("%d", state[j]);
            if(j != N-1){
                // Do nothing, as per no extra spaces
            }
        }
        printf("\n");
    }
    free(state);
    return 0;
}