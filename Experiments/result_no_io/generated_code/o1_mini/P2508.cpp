#include <stdio.h>
#include <math.h>

typedef long long ll;

int main(){
    ll r;
    scanf("%lld", &r);
    if(r == 0){
        printf("1\n");
        return 0;
    }
    ll n = r;
    ll res = 1;
    // Check for factor 2
    while(n % 2 == 0){
        n /= 2;
    }
    // Trial division for odd primes
    for(ll p=3; p*p <= n; p+=2){
        if(n % p == 0){
            int count = 0;
            while(n % p == 0){
                count++;
                n /= p;
            }
            if(p % 4 ==1){
                res *= (2*count +1);
            }
        }
    }
    if(n >1){
        if(n %4 ==1){
            res *= 3;
        }
    }
    printf("%lld\n", res *4);
    return 0;
}