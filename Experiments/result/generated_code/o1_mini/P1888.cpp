#include <stdio.h>
#include <stdint.h>

typedef long long ll;

// Function to compute gcd using Euclidean algorithm
ll gcd(ll a, ll b){
    while(b != 0){
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(){
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    
    // Identify hypotenuse
    ll hyp = a;
    ll leg1 = b;
    ll leg2 = c;
    
    if(b > hyp){
        hyp = b;
        leg1 = a;
        leg2 = c;
    }
    if(c > hyp){
        hyp = c;
        leg1 = a;
        leg2 = b;
    }
    
    // Identify smaller leg
    ll smaller_leg = leg1 < leg2 ? leg1 : leg2;
    
    // Compute gcd
    ll divisor = gcd(smaller_leg, hyp);
    
    // Reduce fraction
    ll numerator = smaller_leg / divisor;
    ll denominator = hyp / divisor;
    
    printf("%lld/%lld\n", numerator, denominator);
    
    return 0;
}