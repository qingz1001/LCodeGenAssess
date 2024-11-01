#include <stdio.h>
#include <string.h>

int main(){
    char S[5005];
    unsigned long long T;
    scanf("%s", S);
    scanf("%llu", &T);
    int len = strlen(S);
    long long dx_cycle = 0, dy_cycle = 0;
    for(int i=0;i<len;i++){
        switch(S[i]){
            case 'E': dx_cycle +=1; break;
            case 'S': dy_cycle -=1; break;
            case 'W': dx_cycle -=1; break;
            case 'N': dy_cycle +=1; break;
        }
    }
    unsigned long long cycles = T / len;
    unsigned long long rem = T % len;
    long long dx_partial =0, dy_partial=0;
    for(int i=0;i<rem;i++){
        switch(S[i]){
            case 'E': dx_partial +=1; break;
            case 'S': dy_partial -=1; break;
            case 'W': dx_partial -=1; break;
            case 'N': dy_partial +=1; break;
        }
    }
    long long x = cycles * dx_cycle + dx_partial;
    long long y = cycles * dy_cycle + dy_partial;
    printf("%lld %lld\n", x, y);
    return 0;
}