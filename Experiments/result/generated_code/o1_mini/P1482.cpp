#include <stdio.h>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

// Function to compute gcd
int gcd_func(int a, int b){
    while(b != 0){
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Function to parse a fraction string into numerator and denominator
Fraction parse_fraction(char *s){
    Fraction f;
    sscanf(s, "%d/%d", &f.numerator, &f.denominator);
    return f;
}

int main(){
    char s1[20], s2[20];
    scanf("%s", s1);
    scanf("%s", s2);
    
    Fraction f1 = parse_fraction(s1);
    Fraction f2 = parse_fraction(s2);
    
    long long p = (long long)f1.numerator * f2.numerator;
    long long q = (long long)f1.denominator * f2.denominator;
    
    long long g = gcd_func(p < 0 ? -p : p, q < 0 ? -q : q);
    
    p /= g;
    q /= g;
    
    int i, j;
    if(q == 1){
        i = p;
        j = 1;
    }
    else if(p == 1){
        i = 1;
        j = q;
    }
    else{
        i = p;
        j = q;
    }
    
    printf("%d %d\n", j, i);
    
    return 0;
}