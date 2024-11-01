#include <stdio.h>

typedef unsigned long long ull;

int sum_of_digits(ull x) {
    int sum = 0;
    while(x > 0){
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main(){
    ull L, R;
    if(scanf("%llu %llu", &L, &R) != 2){
        return 1;
    }
    int count = 0;
    for(ull x = L; x <= R; x++){
        int s = sum_of_digits(x);
        ull y = x * x;
        int s2 = sum_of_digits(y);
        if(s2 == s * s){
            count++;
        }
        if(x == ULLONG_MAX){
            break;
        }
    }
    printf("%d\n", count);
    return 0;
}