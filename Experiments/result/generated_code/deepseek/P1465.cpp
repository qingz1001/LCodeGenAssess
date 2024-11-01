#include <stdio.h>

void countRomanChars(int n, int *counts) {
    char roman[13][3] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char chars[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int charCounts[7] = {0};

    for (int i = 0; i < 13; i++) {
        while (n >= values[i]) {
            n -= values[i];
            for (int j = 0; roman[i][j]; j++) {
                switch (roman[i][j]) {
                    case 'I': charCounts[0]++; break;
                    case 'V': charCounts[1]++; break;
                    case 'X': charCounts[2]++; break;
                    case 'L': charCounts[3]++; break;
                    case 'C': charCounts[4]++; break;
                    case 'D': charCounts[5]++; break;
                    case 'M': charCounts[6]++; break;
                }
            }
        }
    }

    for (int i = 0; i < 7; i++) {
        counts[i] += charCounts[i];
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int counts[7] = {0};

    for (int i = 1; i <= n; i++) {
        countRomanChars(i, counts);
    }

    char chars[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    for (int i = 0; i < 7; i++) {
        if (counts[i] > 0) {
            printf("%c %d\n", chars[i], counts[i]);
        }
    }

    return 0;
}