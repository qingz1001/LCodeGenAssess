#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_DIGITS 100
#define MAX_PRIMES 1000
#define MAX_INPUT 1000

// Function to generate prime numbers using Sieve of Eratosthenes
int generate_primes(int *primes, int max_count) {
    int size = 10000;
    char *is_prime = calloc(size, sizeof(char));
    memset(is_prime, 1, size);
    is_prime[0] = is_prime[1] = 0;
    int count = 0;
    for(int i=2;i<size && count < max_count;i++) {
        if(is_prime[i]){
            primes[count++] = i;
            for(int j=2*i; j<size; j+=i){
                is_prime[j] = 0;
            }
        }
    }
    free(is_prime);
    return count;
}

// Function to split a string by a delimiter and store integers
int split_string(char *str, char delim, int *digits){
    int count = 0;
    char *token = strtok(str, &delim);
    while(token){
        digits[count++] = atoi(token);
        token = strtok(NULL, &delim);
    }
    return count;
}

int main(){
    char input[MAX_INPUT];
    fgets(input, sizeof(input), stdin);
    // Remove possible newline
    input[strcspn(input, "\n")] = 0;
    
    // Split the input into two parts by '+'
    char *plus = strchr(input, '+');
    if(!plus){
        // Invalid input
        return 0;
    }
    *plus = '\0';
    char *A_str = input;
    char *B_str = plus +1;
    
    // Split A and B by ','
    int A_digits[MAX_DIGITS];
    int B_digits[MAX_DIGITS];
    char A_copy[MAX_INPUT], B_copy[MAX_INPUT];
    strcpy(A_copy, A_str);
    strcpy(B_copy, B_str);
    int A_len = split_string(A_copy, ',', A_digits);
    int B_len = split_string(B_copy, ',', B_digits);
    
    // Reverse the digits to make index 0 as least significant
    for(int i=0;i<A_len/2;i++){
        int temp = A_digits[i];
        A_digits[i] = A_digits[A_len-1-i];
        A_digits[A_len-1-i] = temp;
    }
    for(int i=0;i<B_len/2;i++){
        int temp = B_digits[i];
        B_digits[i] = B_digits[B_len-1-i];
        B_digits[B_len-1-i] = temp;
    }
    
    // Generate primes
    int primes[MAX_PRIMES];
    int prime_count = generate_primes(primes, MAX_DIGITS);
    
    // Add the numbers
    int result[MAX_DIGITS +1];
    int res_len =0;
    int carry =0;
    int max_len = (A_len > B_len) ? A_len : B_len;
    for(int i=0;i<max_len || carry; i++){
        int a = (i < A_len) ? A_digits[i] : 0;
        int b = (i < B_len) ? B_digits[i] : 0;
        int base = (i < prime_count) ? primes[i] : primes[prime_count-1];
        int sum = a + b + carry;
        result[res_len++] = sum % base;
        carry = sum / base;
    }
    
    // Reverse the result to high to low
    for(int i=0;i<res_len/2;i++){
        int temp = result[i];
        result[i] = result[res_len-1-i];
        result[res_len-1-i] = temp;
    }
    
    // Print the result
    for(int i=0;i<res_len;i++){
        if(i>0) printf(",");
        printf("%d", result[i]);
    }
    return 0;
}