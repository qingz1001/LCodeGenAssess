#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_palindrome(int num, int base){
    char digits[32];
    int idx = 0;
    if(num == 0){
        digits[idx++] = '0';
    }
    while(num > 0){
        digits[idx++] = '0' + (num % base);
        num /= base;
    }
    for(int i = 0; i < idx / 2; i++){
        if(digits[i] != digits[idx - 1 - i]){
            return 0;
        }
    }
    return 1;
}

int main(){
    int n, s;
    scanf("%d %d", &n, &s);
    int count = 0;
    int num = s + 1;
    while(count < n){
        int pal_count = 0;
        for(int base = 2; base <= 10; base++){
            if(is_palindrome(num, base)){
                pal_count++;
                if(pal_count >= 2){
                    break;
                }
            }
        }
        if(pal_count >= 2){
            printf("%d\n", num);
            count++;
        }
        num++;
    }
    return 0;
}