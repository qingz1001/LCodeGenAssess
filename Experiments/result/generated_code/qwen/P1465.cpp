#include <stdio.h>
#include <string.h>

void countRomanDigits(int n) {
    const char* roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    int counts[13] = {0};

    for (int i = 0; i < 13; i++) {
        while (n >= values[i]) {
            n -= values[i];
            counts[i]++;
        }
    }

    for (int i = 0; i < 13; i++) {
        if (counts[i] > 0) {
            printf("%s %d\n", roman[i], counts[i]);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    countRomanDigits(n);
    return 0;
}