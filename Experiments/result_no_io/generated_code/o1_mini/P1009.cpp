#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

typedef struct {
    int digits[MAX_DIGITS];
    int length;
} BigInt;

void initBigInt(BigInt *num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->length = 1;
    num->digits[0] = 0;
}

void copyBigInt(BigInt *dest, BigInt *src) {
    memcpy(dest->digits, src->digits, sizeof(src->digits));
    dest->length = src->length;
}

void multiplyBigInt(BigInt *num, int x) {
    int carry = 0;
    for(int i = 0; i < num->length; i++) {
        int temp = num->digits[i] * x + carry;
        num->digits[i] = temp % 10;
        carry = temp / 10;
    }
    while(carry) {
        num->digits[num->length] = carry % 10;
        carry /= 10;
        num->length++;
    }
}

void addBigInt(BigInt *a, BigInt *b) {
    int carry = 0;
    int max = a->length > b->length ? a->length : b->length;
    for(int i = 0; i < max; i++) {
        a->digits[i] += (i < b->length ? b->digits[i] : 0) + carry;
        if(a->digits[i] >= 10) {
            a->digits[i] -= 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
    }
    if(carry) {
        a->digits[max] += carry;
        if(a->digits[max] >=10){
            a->digits[max] -=10;
            a->length = max +2;
            a->digits[max+1] +=1;
        }
        else {
            a->length = max +1;
        }
    }
    if(a->length < max) a->length = max;
}

int main(){
    int n;
    scanf("%d", &n);
    BigInt sum, fact, temp;
    initBigInt(&sum);
    initBigInt(&fact);
    fact.digits[0] = 1;
    fact.length = 1;
    for(int i = 1; i <= n; i++){
        multiplyBigInt(&fact, i);
        addBigInt(&sum, &fact);
    }
    for(int i = sum.length -1; i >=0; i--){
        printf("%d", sum.digits[i]);
    }
    return 0;
}