#include <stdio.h>

long long factorial[11];

long long power_pow(int x, int y){
    if(x == 0 && y == 0) return 1;
    long long res = 1;
    for(int i = 0; i < y; i++) {
        res *= x;
    }
    return res;
}

int main(){
    int n, r;
    scanf("%d %d", &n, &r);
    
    // Compute factorial
    factorial[0] = 1;
    for(int i = 1; i <= 10; i++) {
        factorial[i] = factorial[i-1] * i;
    }
    
    long long ans = 0;
    
    if(r == 0){
        if(n == 0) ans = 1;
        else ans = 0;
    }
    else{
        for(int k = 0; k <= r; k++){
            // Compute sign
            long long sign = (k % 2 == 0) ? 1 : -1;
            
            // Compute C(r,k)
            long long C = factorial[r] / (factorial[k] * factorial[r - k]);
            
            // Compute (r - k)^n
            long long P = power_pow(r - k, n);
            
            // Add to answer
            ans += sign * C * P;
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}