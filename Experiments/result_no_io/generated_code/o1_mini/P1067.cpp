#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int n;
    scanf("%d", &n);
    int coeffs[101];
    for(int i=0;i<=n;i++) scanf("%d", &coeffs[i]);
    int first = 1;
    for(int i=0;i<=n;i++){
        int degree = n - i;
        int coef = coeffs[i];
        if(coef == 0) continue;
        if(first){
            if(coef < 0){
                printf("-");
            }
        }
        else{
            if(coef > 0){
                printf("+");
            }
            else{
                printf("-");
            }
        }
        if(first){
            if(coef <0) coef = -coef;
        }
        else{
            if(coef <0) coef = -coef;
        }
        int need_coef = 1;
        if(coef ==1 && degree !=0){
            need_coef =0;
        }
        if(need_coef){
            printf("%d", coef);
        }
        if(degree >1){
            printf("x^%d", degree);
        }
        else if(degree ==1){
            printf("x");
        }
        first =0;
    }
    return 0;
}