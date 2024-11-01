#include <stdio.h>
#include <math.h>

int main(){
    long long a, b;
    scanf("%lld %lld", &a, &b);
    if(a > b){
        long long tmp = a;
        a = b;
        b = tmp;
    }
    long long k = b - a;
    if(k == 0){
        // Both heaps are equal, first player can take all and win
        printf("1\n");
        return 0;
    }
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    long long a_calc = (long long)floor(k * phi);
    if(a == a_calc){
        printf("0\n");
    }
    else{
        printf("1\n");
    }
}