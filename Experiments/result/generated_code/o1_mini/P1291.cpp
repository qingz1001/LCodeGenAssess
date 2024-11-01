#include <stdio.h>
#include <stdlib.h>

// Function to compute gcd
unsigned long long gcd_func(unsigned long long a, unsigned long long b){
    while(b){
        unsigned long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Function to compute lcm
unsigned long long lcm_func(unsigned long long a, unsigned long long b){
    return a / gcd_func(a, b) * b;
}

// Function to count digits
int count_digits(unsigned long long num){
    if(num ==0) return 1;
    int cnt=0;
    while(num){
        cnt++;
        num /=10;
    }
    return cnt;
}

int main(){
    int n;
    scanf("%d", &n);
    
    // Compute lcm of 1 to n
    unsigned long long lcm =1;
    for(int k=2; k<=n; k++){
        lcm = lcm_func(lcm, k);
    }
    
    // Compute sum = sum(lcm /k) for k=1 to n
    unsigned long long sum =0;
    for(int k=1; k<=n; k++){
        sum += lcm /k;
    }
    
    // E = sum *n / lcm
    unsigned long long numer = sum * (unsigned long long)n;
    unsigned long long denom = lcm;
    
    // Reduce fraction
    unsigned long long g = gcd_func(numer, denom);
    numer /=g;
    denom /=g;
    
    if(denom ==1){
        printf("%llu\n", numer);
    }
    else{
        unsigned long long integer_part = numer / denom;
        unsigned long long fraction_numer = numer % denom;
        int len_den = count_digits(denom);
        
        if(integer_part >0){
            printf("%llu\n", fraction_numer);
            printf("%llu", integer_part);
            for(int i=0;i<len_den;i++) printf("-");
            printf("\n%llu\n", denom);
        }
        else{
            printf("%llu\n", fraction_numer);
            printf("0");
            for(int i=0;i<len_den;i++) printf("-");
            printf("\n%llu\n", denom);
        }
    }
    
    return 0;
}