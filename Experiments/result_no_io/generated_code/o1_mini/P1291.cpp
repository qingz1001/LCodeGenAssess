#include <stdio.h>

typedef unsigned long long ull;

// Function to compute GCD using Euclidean algorithm
ull gcd_func(ull a, ull b){
    while(b){
        ull temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Function to count the number of digits in a number
int count_digits(ull num){
    if(num == 0) return 1;
    int count = 0;
    while(num){
        count++;
        num /=10;
    }
    return count;
}

int main(){
    int n;
    scanf("%d", &n);
    
    ull sum_num = 0, sum_den =1;
    
    for(int k=1; k<=n; k++){
        ull term_num = n;
        ull term_den = k;
        
        // sum_num/sum_den + term_num/term_den
        ull new_num = sum_num * term_den + sum_den * term_num;
        ull new_den = sum_den * term_den;
        
        // Reduce the fraction
        ull g = gcd_func(new_num, new_den);
        sum_num = new_num / g;
        sum_den = new_den / g;
    }
    
    ull integer_part = sum_num / sum_den;
    ull fraction_num = sum_num % sum_den;
    
    if(fraction_num ==0){
        printf("%llu\n", integer_part);
    }
    else{
        ull fraction_den = sum_den;
        ull g = gcd_func(fraction_num, fraction_den);
        fraction_num /= g;
        fraction_den /= g;
        
        // Count digits in denominator
        int den_digits = count_digits(fraction_den);
        
        printf("%llu\n", fraction_num);
        printf("%llu", integer_part);
        for(int i=0;i<den_digits;i++) printf("-");
        printf("\n%llu\n", fraction_den);
    }
    
    return 0;
}