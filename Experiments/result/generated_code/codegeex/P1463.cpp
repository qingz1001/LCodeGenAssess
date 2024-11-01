#include <stdio.h>
#include <math.h>

long long maxDivisors = 0;
long long maxNumber = 0;

void findHighlyCompositeNumber(long long n, long long currentNumber, long long currentDivisors, long long primeFactor, long long exponent) {
    if (currentNumber > n) return;
    if (currentDivisors > maxDivisors || (currentDivisors == maxDivisors && currentNumber < maxNumber)) {
        maxDivisors = currentDivisors;
        maxNumber = currentNumber;
    }
    for (long long i = 1; i <= exponent; i++) {
        long long newNumber = currentNumber * pow(primeFactor, i);
        if (newNumber > n) break;
        findHighlyCompositeNumber(n, newNumber, currentDivisors * (i + 1), primeFactor, exponent);
    }
}

int main() {
    long long n;
    scanf("%lld", &n);
    for (long long primeFactor = 2; primeFactor <= 100; primeFactor++) {
        long long exponent = 1;
        while (pow(primeFactor, exponent) <= n) exponent++;
        exponent--;
        findHighlyCompositeNumber(n, primeFactor, 2, primeFactor, exponent);
    }
    printf("%lld\n", maxNumber);
    return 0;
}