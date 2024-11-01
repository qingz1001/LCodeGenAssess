#include <stdio.h>
#include <math.h>

int main(){
    long long x0, y0;
    scanf("%lld %lld", &x0, &y0);
    if(y0 % x0 != 0){
        printf("0\n");
        return 0;
    }
    long long n = y0 / x0;
    if(n ==1){
        printf("1\n");
        return 0;
    }
    int count =0;
    for(long long i=2; i*i <=n; i++){
        if(n % i ==0){
            count++;
            while(n % i ==0){
                n /=i;
            }
        }
    }
    if(n >1){
        count++;
    }
    long long res =1;
    for(int i=0;i<count;i++) res *=2;
    printf("%lld\n", res);
    return 0;
}