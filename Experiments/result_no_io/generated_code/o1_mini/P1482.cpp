#include <stdio.h>

// Function to compute gcd using Euclidean algorithm
int gcd(int a, int b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

int main(){
    int p1, q1, p2, q2;
    // Read first fraction
    scanf("%d/%d", &p1, &q1);
    // Read second fraction
    scanf("%d/%d", &p2, &q2);
    
    // Multiply the fractions
    long long numerator = (long long)p1 * p2;
    long long denominator = (long long)q1 * q2;
    
    // Simplify the fraction
    int g = gcd(numerator < 0 ? -numerator : numerator, denominator < 0 ? -denominator : denominator);
    numerator /= g;
    denominator /= g;
    
    // Ensure denominator is positive
    if(denominator < 0){
        numerator = -numerator;
        denominator = -denominator;
    }
    
    // Determine the position in the table
    if(numerator % denominator == 0){
        // It's an integer, treat as a/1
        printf("1 %lld\n", numerator / denominator);
    }
    else if(numerator == 1){
        // It's of the form 1/a
        printf("%lld 1\n", denominator);
    }
    else{
        // It's of the form a/b
        printf("%lld %lld\n", denominator, numerator);
    }
    
    return 0;
}