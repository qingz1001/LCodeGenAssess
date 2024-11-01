#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 300

typedef struct {
    int digits[MAX_DIGITS];
    int len;
} BigInt;

// Initialize BigInt to 1
void init_bigint(BigInt *num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->digits[0] = 1;
    num->len = 1;
}

// Multiply BigInt by 2
void multiply_by_two(BigInt *num) {
    int carry = 0;
    for(int i=0;i<num->len;i++) {
        int temp = num->digits[i]*2 + carry;
        num->digits[i] = temp %10;
        carry = temp /10;
    }
    if(carry) {
        num->digits[num->len++] = carry;
    }
}

// Multiply BigInt by small integer (n-1)
void multiply_by_small(BigInt *num, int multiplier) {
    int carry = 0;
    for(int i=0;i<num->len;i++) {
        long temp = (long)num->digits[i] * multiplier + carry;
        num->digits[i] = temp %10;
        carry = temp /10;
    }
    while(carry) {
        num->digits[num->len++] = carry %10;
        carry /=10;
    }
}

// Print BigInt
void print_bigint(BigInt *num) {
    for(int i=num->len-1;i>=0;i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    if(n ==1){
        printf("1\n");
        return 0;
    }
    else if(n==2){
        printf("3\n");
        return 0;
    }
    BigInt num;
    init_bigint(&num);
    for(int i=0;i<n;i++) {
        multiply_by_two(&num);
    }
    multiply_by_small(&num, n-1);
    print_bigint(&num);
    return 0;
}