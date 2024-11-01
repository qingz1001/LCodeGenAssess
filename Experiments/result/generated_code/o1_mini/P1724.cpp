#include <stdio.h>
#include <string.h>

int main(){
    char S[5005];
    unsigned long long T;
    scanf("%s", S);
    scanf("%llu", &T);
    int len = strlen(S);
    long long dx =0, dy =0;
    for(int i=0;i<len;i++){
        switch(S[i]){
            case 'E': dx +=1; break;
            case 'W': dx -=1; break;
            case 'N': dy +=1; break;
            case 'S': dy -=1; break;
        }
    }
    unsigned long long k = T / len;
    unsigned long long rem = T % len;
    long long total_x = k * dx;
    long long total_y = k * dy;
    for(int i=0;i<rem;i++){
        switch(S[i]){
            case 'E': total_x +=1; break;
            case 'W': total_x -=1; break;
            case 'N': total_y +=1; break;
            case 'S': total_y -=1; break;
        }
    }
    printf("%lld %lld\n", total_x, total_y);
}