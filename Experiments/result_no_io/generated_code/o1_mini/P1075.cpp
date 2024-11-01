#include <stdio.h>
#include <math.h>

int main(){
    long n;
    scanf("%ld", &n);
    long i;
    for(i = 2; i <= sqrt((double)n); i++){
        if(n % i == 0){
            printf("%ld\n", n / i);
            return 0;
        }
    }
    return 0;
}