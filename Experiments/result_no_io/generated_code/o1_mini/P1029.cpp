#include <stdio.h>

int main(){
    long long x0, y0;
    scanf("%lld %lld", &x0, &y0);
    if(y0 % x0 !=0){
        printf("0\n");
        return 0;
    }
    long long K = y0 / x0;
    if(K ==1){
        printf("1\n");
        return 0;
    }
    int count =0;
    for(long long i=2;i*i<=K;i++){
        if(K %i ==0){
            count++;
            while(K %i ==0){
                K /=i;
            }
        }
    }
    if(K >1){
        count++;
    }
    long long res =1;
    for(int i=0;i<count;i++) res *=2;
    printf("%lld\n", res);
}