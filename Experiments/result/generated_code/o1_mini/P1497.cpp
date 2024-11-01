#include <stdio.h>
#include <string.h>

typedef struct {
    int digits[10000];
    int len;
} BigInt;

// Function to initialize BigInt to 1
void init_bigint(BigInt *num) {
    num->digits[0] = 1;
    num->len = 1;
    memset(num->digits + 1, 0, sizeof(int) * 9999);
}

// Function to multiply BigInt by a small integer x
void multiply_bigint(BigInt *num, int x) {
    int carry = 0;
    for(int i = 0; i < num->len; i++) {
        long long temp = (long long)num->digits[i] * x + carry;
        num->digits[i] = temp % 10;
        carry = temp / 10;
    }
    while(carry > 0) {
        num->digits[num->len++] = carry % 10;
        carry /= 10;
    }
}

// Function to print BigInt
void print_bigint(BigInt *num) {
    for(int i = num->len -1; i >=0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

int main(){
    int n, k, h;
    scanf("%d %d %d", &n, &k, &h);
    int c[20];
    for(int i=0;i<h;i++) scanf("%d", &c[i]);
    // Define primes up to 20
    int primes[8] = {2,3,5,7,11,13,17,19};
    // Precompute exponents for factorials up to 20
    int exponents_fact[21][8];
    for(int j=0; j<8; j++) exponents_fact[0][j] =0;
    for(int i=1;i<=20;i++){
        for(int j=0; j<8; j++) exponents_fact[i][j] = exponents_fact[i-1][j];
        int temp = i;
        for(int j=0; j<8; j++){
            while(temp % primes[j] ==0){
                exponents_fact[i][j]++;
                temp /= primes[j];
            }
        }
    }
    // Compute exponents
    int final_exp[8];
    for(int j=0; j<8; j++){
        // 2*(exponents_fact[n][j] - exponents_fact[n -k][j])
        int exp = 2 * (exponents_fact[n][j] - (k <= n ? exponents_fact[n -k][j] : 0));
        // Subtract sum of exponents of c_i!
        for(int i=0;i<h;i++) {
            if(c[i] <=20){
                exp -= exponents_fact[c[i]][j];
            }
        }
        final_exp[j] = exp;
    }
    // Initialize BigInt to 1
    BigInt num;
    init_bigint(&num);
    // Multiply by primes[j] exponent[j] times
    for(int j=0; j<8; j++){
        for(int e=0; e<final_exp[j]; e++) {
            multiply_bigint(&num, primes[j]);
        }
    }
    // Handle k=0 separately
    if(k ==0){
        printf("1\n");
        return 0;
    }
    // Print the result
    print_bigint(&num);
    return 0;
}