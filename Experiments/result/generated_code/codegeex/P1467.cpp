#include <stdio.h>
#include <stdbool.h>

bool isCircularNumber(unsigned long long num) {
    int digits[10];
    int count = 0;
    unsigned long long original = num;
    
    // Extract digits and check for duplicates
    while (num > 0) {
        int digit = num % 10;
        if (digit == 0) return false; // Contains zero
        for (int i = 0; i < count; i++) {
            if (digits[i] == digit) return false; // Duplicates
        }
        digits[count++] = digit;
        num /= 10;
    }
    
    // Check if each digit is visited exactly once
    int index = 0;
    for (int i = 0; i < count; i++) {
        num = original;
        for (int j = 0; j < digits[index]; j++) {
            num /= 10;
            if (num == 0) num = original;
        }
        if (num % 10 != digits[(index + digits[index]) % count]) return false;
        index = (index + digits[index]) % count;
    }
    
    return true;
}

unsigned long long findNextCircularNumber(unsigned long long m) {
    unsigned long long num = m + 1;
    while (true) {
        if (isCircularNumber(num)) return num;
        num++;
    }
}

int main() {
    unsigned long long m;
    scanf("%llu", &m);
    unsigned long long result = findNextCircularNumber(m);
    printf("%llu\n", result);
    return 0;
}