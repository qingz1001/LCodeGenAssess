#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to hold prime factors
typedef struct {
    int prime;
    long long exponent;
} Factor;

// Function to factorize a number and store primes and exponents
int factorize(int num, Factor factors[]) {
    int count = 0;
    // Check for factor 2
    long long exp = 0;
    while (num % 2 == 0) {
        exp++;
        num /= 2;
    }
    if (exp > 0) {
        factors[count].prime = 2;
        factors[count].exponent = exp;
        count++;
    }
    // Check for odd factors
    for(int i=3;i<=sqrt(num);i+=2){
        if(num%i ==0){
            exp =0;
            while(num%i ==0){
                exp++;
                num /=i;
            }
            factors[count].prime = i;
            factors[count].exponent = exp;
            count++;
        }
    }
    if(num >1){
        factors[count].prime = num;
        factors[count].exponent =1;
        count++;
    }
    return count;
}

// Function to count exponent of prime in a number
long long count_factor(int num, int prime){
    long long cnt =0;
    while(num % prime ==0){
        cnt++;
        num /= prime;
    }
    return cnt;
}

int main(){
    int N;
    scanf("%d", &N);
    int m1;
    long long m2;
    scanf("%d %lld", &m1, &m2);
    // Factorize m1
    Factor m1_factors[20];
    int m1_cnt = factorize(m1, m1_factors);
    // If m1 ==1, M=1
    if(m1 ==1){
        printf("0");
        return 0;
    }
    // Calculate required exponents in M
    long long required_exp[20];
    for(int i=0;i<m1_cnt;i++){
        required_exp[i] = m1_factors[i].exponent * m2;
    }
    // Read S_i
    long long S;
    long long min_t = -1;
    for(int i=0;i<N;i++){
        scanf("%lld", &S);
        // For each prime factor, count exponent in S
        long long t = 0;
        int valid = 1;
        for(int j=0;j<m1_cnt;j++){
            int p = m1_factors[j].prime;
            long long e =0;
            long long temp = S;
            while(temp % p ==0){
                e++;
                temp /=p;
            }
            if(e ==0){
                valid =0;
                break;
            }
            long long current_t = (required_exp[j] + e -1) / e;
            if(current_t > t){
                t = current_t;
            }
        }
        if(valid){
            if(min_t == -1 || t < min_t){
                min_t = t;
            }
        }
    }
    printf("%lld", min_t);
    return 0;
}