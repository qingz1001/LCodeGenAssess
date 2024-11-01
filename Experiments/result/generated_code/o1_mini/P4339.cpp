#include <stdio.h>
#include <math.h>

// Function to compute Euler's Totient Function
long long phi(long long n){
    if(n == 0) return 0;
    long long result = n;
    for(long long i=2; i*i <=n; i++){
        if(n%i ==0){
            while(n%i ==0){
                n /=i;
            }
            result -= result /i;
        }
    }
    if(n >1){
        result -= result /n;
    }
    return result;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        long long m,K;
        scanf("%lld %lld",&m,&K);
        if(K ==0){
            printf("-1\n");
            continue;
        }
        long long tot = phi(K);
        printf("%lld\n", tot +1);
    }
    return 0;
}