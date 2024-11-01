#include <stdio.h>

int main(){
    long long n;
    scanf("%lld", &n);
    int m = 0;
    while ((1LL << (m + 2)) < n){
        m += 2;
    }
    printf("%d\n", m);
    return 0;
}