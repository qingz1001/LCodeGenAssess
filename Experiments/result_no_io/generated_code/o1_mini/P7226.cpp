#include <stdio.h>

long long power(int base, int exp){
    long long result = 1;
    for(int i=0;i<exp;i++) result *= base;
    return result;
}

int main(){
    int n;
    scanf("%d", &n);
    long long X = 0;
    for(int i=0;i<n;i++){
        int q;
        scanf("%d", &q);
        int p = q % 10;
        int num = q / 10;
        X += power(num, p);
    }
    printf("%lld\n", X);
    return 0;
}