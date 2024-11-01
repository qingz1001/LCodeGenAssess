#include <stdio.h>

int main(){
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);
    
    int minRB = R < B ? R : B;
    long long maxTotal = -1000000000LL; // Initialize to a very small number
    
    for(int b = 0; b <= minRB; b++){
        long long total = (long long)(R - b) * C + (long long)(B - b) * D + 2LL * b * E;
        if(total > maxTotal){
            maxTotal = total;
        }
    }
    
    printf("%lld\n", maxTotal);
    return 0;
}