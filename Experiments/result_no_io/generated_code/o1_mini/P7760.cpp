#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, X;
    scanf("%d", &N);
    scanf("%d", &X);
    int total = 0;
    for(int i=0;i<N;i++){
        int P1, P2;
        scanf("%d %d", &P1, &P2);
        int diff = abs(P1 - P2);
        if(diff <= X){
            if(P1 > P2){
                total += P1;
            }
            else{
                total += P2;
            }
        }
        else{
            int P3;
            scanf("%d", &P3);
            total += P3;
        }
    }
    printf("%d", total);
    return 0;
}