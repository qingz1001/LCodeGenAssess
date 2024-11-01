#include <stdio.h>
#include <math.h>

int countDivisors(int n) {
    int count = 0;
    int sqrtN = sqrt(n);
    
    for (int i = 1; i <= sqrtN; i++) {
        if (n % i == 0) {
            if (n / i == i) {
                count++;
            } else {
                count += 2;
            }
        }
    }
    
    return count;
}

int main() {
    int L, U;
    scanf("%d %d", &L, &U);
    
    int maxDivisors = 0;
    int numWithMaxDivisors = 0;
    
    for (int i = L; i <= U; i++) {
        int divisors = countDivisors(i);
        if (divisors > maxDivisors) {
            maxDivisors = divisors;
            numWithMaxDivisors = i;
        }
    }
    
    printf("Between %d and %d, %d has a maximum of %d divisors.\n", 
           L, U, numWithMaxDivisors, maxDivisors);
    
    return 0;
}