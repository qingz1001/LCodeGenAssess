#include <stdio.h>
#include <stdlib.h>

int main(){
    long long n;
    scanf("%lld", &n);
    if(n & 1){
        printf("-1\n");
        return 0;
    }
    long long powers[32];
    int count =0;
    long long power =1;
    while(n >0){
        if((n &1) && power >=2){
            powers[count++] = power;
        }
        n >>=1;
        power <<=1;
    }
    if(count ==0){
        printf("-1\n");
        return 0;
    }
    for(int i=count-1;i>=0;i--){
        printf("%lld", powers[i]);
        if(i !=0) printf(" ");
    }
    printf("\n");
    return 0;
}