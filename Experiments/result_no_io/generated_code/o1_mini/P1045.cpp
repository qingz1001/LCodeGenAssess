#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    int digits[500];
} BigInt;

// Initialize BigInt to zero
void initBigInt(BigInt *a) {
    for(int i = 0; i < 500; i++) {
        a->digits[i] = 0;
    }
}

// Copy BigInt src to dest
void copyBigInt(BigInt *dest, BigInt *src) {
    for(int i = 0; i < 500; i++) {
        dest->digits[i] = src->digits[i];
    }
}

// Multiply a and b, store result in res (res = a * b mod 10^500)
void multiplyBigInt(BigInt *a, BigInt *b, BigInt *res) {
    BigInt temp;
    initBigInt(&temp);
    for(int i = 0; i < 500; i++) {
        if(a->digits[i] == 0) continue;
        int carry = 0;
        for(int j = 0; j + i < 500 && j < 500; j++) {
            if(b->digits[j] == 0) continue;
            long long sum = (long long)a->digits[i] * b->digits[j] + temp.digits[i+j] + carry;
            temp.digits[i+j] = sum % 10;
            carry = sum / 10;
        }
    }
    copyBigInt(res, &temp);
}

// Subtract 1 from a BigInt a (a = a - 1)
void subtractOne(BigInt *a) {
    int i = 0;
    while(i < 500) {
        if(a->digits[i] > 0) {
            a->digits[i]--;
            break;
        }
        else {
            a->digits[i] = 9;
            i++;
        }
    }
}

// Convert BigInt to string with leading zeros
void bigIntToString(BigInt *a, char *str) {
    for(int i = 499; i >=0; i--) {
        str[499 - i] = a->digits[i] + '0';
    }
    str[500] = '\0';
}

int main(){
    long long P;
    scanf("%lld", &P);
    
    // Calculate number of digits
    double log2 = 0.3010299956639812;
    long long numDigits = (long long)(P * log2) + 1;
    printf("%lld\n", numDigits);
    
    // Compute 2^P mod 10^500
    BigInt result, base, temp;
    initBigInt(&result);
    result.digits[0] = 1;
    
    initBigInt(&base);
    base.digits[0] = 2;
    
    long long exponent = P;
    
    while(exponent > 0){
        if(exponent & 1){
            multiplyBigInt(&result, &base, &temp);
            copyBigInt(&result, &temp);
        }
        multiplyBigInt(&base, &base, &temp);
        copyBigInt(&base, &temp);
        exponent >>=1;
    }
    
    // Subtract 1
    subtractOne(&result);
    
    // Convert to string
    char str[501];
    bigIntToString(&result, str);
    
    // Print 10 lines of 50 digits
    for(int i =0;i<10;i++){
        for(int j=0;j<50;j++){
            putchar(str[i*50 + j]);
        }
        putchar('\n');
    }
    
    return 0;
}