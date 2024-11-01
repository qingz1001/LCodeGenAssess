#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd_func(long long a, long long b){
    if(b == 0)
        return a;
    return gcd_func(b, a % b);
}

void simplify(Fraction *f){
    if(f->den < 0){
        f->den = -f->den;
        f->num = -f->num;
    }
    long long g = gcd_func(abs(f->num), abs(f->den));
    f->num /= g;
    f->den /= g;
}

int main(){
    char s[105];
    scanf("%s", s);
    int len = strlen(s);
    int idx = 0;
    Fraction result = {0,1};
    
    // Parse first fraction
    int sign = 1;
    if(s[idx] == '-'){
        sign = -1;
        idx++;
    }
    // Parse numerator
    long long a = 0;
    while(idx < len && s[idx] >= '0' && s[idx] <= '9'){
        a = a *10 + (s[idx]-'0');
        idx++;
    }
    a *= sign;
    // Skip '/'
    idx++;
    // Parse denominator
    long long b = 0;
    while(idx < len && s[idx] >= '0' && s[idx] <= '9'){
        b = b *10 + (s[idx]-'0');
        idx++;
    }
    result.num = a;
    result.den = b;
    simplify(&result);
    
    // Parse remaining fractions
    while(idx < len){
        char op = s[idx];
        idx++;
        // Parse numerator
        sign = 1;
        if(s[idx] == '-'){
            sign = -1;
            idx++;
        }
        a = 0;
        while(idx < len && s[idx] >= '0' && s[idx] <= '9'){
            a = a *10 + (s[idx]-'0');
            idx++;
        }
        a *= sign;
        // Skip '/'
        idx++;
        // Parse denominator
        b = 0;
        while(idx < len && s[idx] >= '0' && s[idx] <= '9'){
            b = b *10 + (s[idx]-'0');
            idx++;
        }
        Fraction temp;
        if(op == '+'){
            temp.num = result.num * b + a * result.den;
            temp.den = result.den * b;
        }
        else { // op == '-'
            temp.num = result.num * b - a * result.den;
            temp.den = result.den * b;
        }
        result = temp;
        simplify(&result);
    }
    
    if(result.den == 1){
        printf("%lld\n", result.num);
    }
    else{
        printf("%lld/%lld\n", result.num, result.den);
    }
    return 0;
}