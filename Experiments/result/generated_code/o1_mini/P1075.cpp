#include <stdio.h>

int main(){
    long n;
    scanf("%ld", &n);
    long factor = 0;
    for(long i = 2; i * i <= n; i++){
        if(n % i == 0){
            factor = i;
            break;
        }
    }
    long other = (factor == 0) ? n : n / factor;
    if(other > factor){
        printf("%ld\n", other);
    }
    else{
        printf("%ld\n", factor);
    }
    return 0;
}