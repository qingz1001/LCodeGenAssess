#include <stdio.h>
#include <stdlib.h>

int magic(int n){
    int digits[10];
    int k = 0;
    if(n == 0){
        digits[k++] = 0;
    }
    while(n > 0){
        digits[k++] = n % 10;
        n /= 10;
    }
    // Reverse digits to get left to right
    for(int i = 0; i < k / 2; i++){
        int tmp = digits[i];
        digits[i] = digits[k - i - 1];
        digits[k - i - 1] = tmp;
    }
    // Compute adjacent absolute differences
    int new_n = 0;
    for(int i = 0; i < k - 1; i++){
        int diff = digits[i] >= digits[i+1] ? digits[i] - digits[i+1] : digits[i+1] - digits[i];
        new_n = new_n * 10 + diff;
    }
    return new_n;
}

int magic_fingerprint(int n){
    while(n >= 10){
        n = magic(n);
    }
    return n;
}

int main(){
    long long A, B;
    if(scanf("%lld%lld", &A, &B)!=2){
        return 0;
    }
    int count = 0;
    for(long long n = A; n <= B; n++){
        int fp = magic_fingerprint((int)n);
        if(fp == 7){
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}