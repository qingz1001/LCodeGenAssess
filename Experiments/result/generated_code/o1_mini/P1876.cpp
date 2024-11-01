#include <stdio.h>
#include <math.h>

int main(){
    unsigned long long N;
    scanf("%llu", &N);
    unsigned long long k_max = (unsigned long long)sqrt((double)N);
    while((k_max + 1) * (k_max + 1) <= N){
        k_max++;
    }
    while(k_max * k_max > N){
        k_max--;
    }
    for(unsigned long long k=1; k<=k_max; k++){
        if(k > 1) printf(" ");
        printf("%llu", k*k);
    }
    printf("\n");
    return 0;
}