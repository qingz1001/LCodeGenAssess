#include <stdio.h>
#include <math.h>

// Function to check if a number is prime
int is_prime(long num) {
    if (num < 2) return 0;
    if (num == 2 || num == 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    long sqrt_num = (long)sqrt((double)num);
    for (long i = 5; i <= sqrt_num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    }
    return 1;
}

// Recursive function to find special primes
void find_special_primes(long current_num, int current_length, int n) {
    if (current_length == n) {
        printf("%ld\n", current_num);
        return;
    }
    for (int digit = 0; digit <= 9; digit++) {
        long next_num = current_num * 10 + digit;
        if (is_prime(next_num)) {
            find_special_primes(next_num, current_length + 1, n);
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    if(n >=1){
        long starting_primes[] = {2, 3, 5, 7};
        for(int i=0;i<4;i++) {
            if(n ==1){
                printf("%ld\n", starting_primes[i]);
            }
            else{
                find_special_primes(starting_primes[i], 1, n);
            }
        }
    }
    return 0;
}