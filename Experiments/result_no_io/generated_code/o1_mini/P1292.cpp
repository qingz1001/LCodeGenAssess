#include <stdio.h>

int main(){
    long long a, b;
    scanf("%lld %lld", &a, &b);
    if(b ==0){
        printf("0\n0 0\n");
        return 0;
    }
    long long k = a / b;
    long long r = a % b;
    long long c, Pa, Pb;
    if(r * 2 > b){
        c = b - r;
        Pa = k;
        Pb = k +1;
    }
    else{
        c = r;
        Pa = k;
        Pb = k;
    }
    printf("%lld\n%lld %lld\n", c, Pa, Pb);
    return 0;
}