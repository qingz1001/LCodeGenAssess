#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_wave(long num, int base){
    if (num == 0)
        return 1;
    char digits[32];
    int len = 0;
    while (num > 0){
        digits[len++] = num % base;
        num /= base;
    }
    if (len == 1)
        return 1;
    for(int i=1;i<len;i++){
        if(digits[i] == digits[i-1])
            return 0;
    }
    for(int i=2;i<len;i++){
        if(digits[i] != digits[i-2])
            return 0;
    }
    return 1;
}

int main(){
    int l, r, k;
    long L, R;
    scanf("%d %d %ld %ld %d", &l, &r, &L, &R, &k);
    for(long N = L; N <= R; N++){
        int count = 0;
        for(int base = l; base <= r; base++){
            if(is_wave(N, base)){
                count++;
                if(count > k)
                    break;
            }
        }
        if(count == k){
            printf("%ld\n", N);
        }
    }
    return 0;
}