#include <stdio.h>

int main(){
    int N, num;
    int present[1001] = {0};
    int sorted[100];
    int M = 0;

    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", &num);
        if(!present[num]){
            present[num] = 1;
        }
    }

    for(int i=1; i<=1000; i++){
        if(present[i]){
            sorted[M++] = i;
        }
    }

    printf("%d\n", M);
    for(int i=0; i<M; i++){
        if(i != 0){
            printf(" ");
        }
        printf("%d", sorted[i]);
    }
    printf("\n");
    return 0;
}