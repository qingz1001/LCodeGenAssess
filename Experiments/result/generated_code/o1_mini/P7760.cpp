#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, X;
    scanf("%d %d", &N, &X);
    int sum = 0;
    for(int i=0;i<N;i++){
        int P1, P2;
        scanf("%d %d", &P1, &P2);
        if(abs(P1 - P2) > X){
            int P3;
            scanf("%d", &P3);
            sum += P3;
        }
        else{
            sum += (P1 > P2) ? P1 : P2;
        }
    }
    printf("%d", sum);
    return 0;
}