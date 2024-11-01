#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_DIGITS 500

typedef struct {
    int digits[MAX_DIGITS];
} BigInt;

// Function to initialize BigInt to a specific value
void init_bigint(BigInt *num, int value) {
    memset(num->digits, 0, sizeof(int) * MAX_DIGITS);
    if (value > 0) {
        num->digits[0] = value;
    }
}

// Function to multiply two BigInts and store the result in res
void multiply(const BigInt *a, const BigInt *b, BigInt *res) {
    int temp[MAX_DIGITS] = {0};
    for(int i = 0; i < MAX_DIGITS; i++) {
        if(a->digits[i] == 0) continue;
        int carry = 0;
        for(int j = 0; j < MAX_DIGITS - i; j++) {
            if(j >= MAX_DIGITS) break;
            if(i + j >= MAX_DIGITS) break;
            long long mul = (long long)a->digits[i] * b->digits[j] + temp[i + j] + carry;
            carry = mul / 10;
            temp[i + j] = mul % 10;
        }
        if(i + MAX_DIGITS < MAX_DIGITS && carry > 0) {
            // Overflow beyond MAX_DIGITS is ignored
        }
    }
    // Copy temp to res
    for(int i = 0; i < MAX_DIGITS; i++) {
        res->digits[i] = temp[i];
    }
}

// Function to copy BigInt src to dest
void copy_bigint(const BigInt *src, BigInt *dest) {
    for(int i = 0; i < MAX_DIGITS; i++) {
        dest->digits[i] = src->digits[i];
    }
}

// Function to subtract one from BigInt
void subtract_one(BigInt *num) {
    int borrow = 1;
    for(int i = 0; i < MAX_DIGITS; i++) {
        num->digits[i] -= borrow;
        if(num->digits[i] < 0) {
            num->digits[i] += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
            break;
        }
    }
}

// Function to perform binary exponentiation: result = base^exp mod 10^500
void power_mod(BigInt *base, long long exp, BigInt *result) {
    BigInt temp_result, temp_base, temp_mult;
    init_bigint(&temp_result, 1);
    copy_bigint(base, &temp_base);

    while(exp > 0) {
        if(exp & 1) {
            multiply(&temp_result, &temp_base, &temp_mult);
            copy_bigint(&temp_mult, &temp_result);
        }
        multiply(&temp_base, &temp_base, &temp_mult);
        copy_bigint(&temp_mult, &temp_base);
        exp >>=1;
    }
    copy_bigint(&temp_result, result);
}

int main(){
    long long P;
    scanf("%lld", &P);

    // Compute number of digits: floor(P * log10(2)) +1
    double log10_2 = 0.3010299956639812;
    long long d = (long long)(P * log10_2) +1;

    // Initialize base =2
    BigInt base;
    init_bigint(&base, 2);

    // Compute 2^P mod 10^500
    BigInt result;
    power_mod(&base, P, &result);

    // Subtract 1
    subtract_one(&result);

    // Print number of digits
    printf("%lld\n", d);

    // Prepare to print last 500 digits
    char output[501];
    memset(output, '0', 500);
    output[500] = '\0';

    if(d <=500){
        // Pad with leading zeros
        for(int i =0; i < d; i++) {
            output[500 - d + i] = result.digits[i] + '0';
        }
    }
    else{
        // Take last 500 digits
        for(int i =0; i <500; i++) {
            output[i] = result.digits[i] + '0';
        }
        // Reverse to correct order
        for(int i =0; i <250; i++) {
            char temp = output[i];
            output[i] = output[499 -i];
            output[499 -i] = temp;
        }
    }

    if(d >500){
        // Reverse to correct order
        for(int i =0; i <500; i++) {
            output[i] = result.digits[i] + '0';
        }
        // Reverse the string
        for(int i =0; i <250; i++) {
            char temp = output[i];
            output[i] = output[499 -i];
            output[499 -i] = temp;
        }
    }
    else{
        // No need to reverse, already placed correctly
    }

    // Now, print in 10 lines of 50 digits each
    for(int i =0; i <10; i++) {
        for(int j =0; j <50; j++) {
            putchar(output[i*50 +j]);
        }
        putchar('\n');
    }

    return 0;
}