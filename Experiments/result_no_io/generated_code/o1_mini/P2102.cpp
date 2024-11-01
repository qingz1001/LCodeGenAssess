#include <stdio.h>

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            if((i + j) % 2 == 0){
                printf("a");
            }
            else{
                printf("b");
            }
        }
        printf("\n");
    }
    return 0;
}