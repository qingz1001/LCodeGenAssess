#include <stdio.h>
#include <stdlib.h>

long long gcd_func(long long a, long long b) {
    while (b != 0) {
        long long tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main(){
    long long a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    // Find the hypotenuse
    long long hyp = a, leg1 = b, leg2 = c;
    if(b > hyp && b*b == a*a + c*c){
        hyp = b;
        leg1 = a;
        leg2 = c;
    }
    if(c > hyp && c*c == a*a + b*b){
        hyp = c;
        leg1 = a;
        leg2 = b;
    }
    // Find the smaller leg
    long long smaller_leg = leg1 < leg2 ? leg1 : leg2;
    long long g = gcd_func(smaller_leg, hyp);
    printf("%lld/%lld\n", smaller_leg/g, hyp/g);
    return 0;
}