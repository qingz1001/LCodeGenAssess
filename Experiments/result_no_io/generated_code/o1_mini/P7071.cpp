#include <stdio.h>

int main(){
    unsigned int n;
    scanf("%u", &n);
    if(n & 1){
        printf("-1\n");
        return 0;
    }
    if(n ==0){
        printf("-1\n");
        return 0;
    }
    unsigned int exponents[32];
    int count =0;
    int exponent =1;
    while((1U << exponent) <=n){
        exponent++;
    }
    exponent--;
    int first =1;
    for(int e=exponent; e>=1; e--){
        if(n & (1U << e)){
            if(!first){
                printf(" ");
            }
            printf("%u", 1U << e);
            first=0;
        }
    }
    printf("\n");
    return 0;
}