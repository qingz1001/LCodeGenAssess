#include <stdio.h>

int main(){
    int N, Pi;
    scanf("%d %d", &N, &Pi);
    long long p_norm = 0, p1_magic = 0, sum_extra = 0;
    for(int i=0;i<N;i++){
        int first, second;
        if(scanf("%d", &first)==1){
            if(scanf("%d", &second)==1){
                // Magic item with P1 and P2
                int P1 = first;
                int P2 = second;
                p1_magic += P1;
                if((P2 - P1) > Pi){
                    sum_extra += (long long)(P2 - P1 - Pi);
                }
            }
            else{
                // Normal item with only P
                p_norm += first;
            }
        }
    }
    printf("%lld\n", p_norm + p1_magic + sum_extra);
}