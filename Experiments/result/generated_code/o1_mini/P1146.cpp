#include <stdio.h>
#include <string.h>

int main(){
    int N;
    scanf("%d", &N);
    printf("%d\n", N);
    char state[N+1];
    for(int i=0;i<N;i++) state[i]='0';
    state[N] = '\0';
    char new_state[N+1];
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(j != i){
                new_state[j] = (state[j] == '0') ? '1' : '0';
            }
            else{
                new_state[j] = state[j];
            }
        }
        new_state[N] = '\0';
        printf("%s\n", new_state);
        strcpy(state, new_state);
    }
    return 0;
}