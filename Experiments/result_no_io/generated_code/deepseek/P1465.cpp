#include <stdio.h>
#include <string.h>

void roman_count(int n, int *count) {
    char roman[13][3] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char roman_chars[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    int roman_counts[7] = {0};

    for (int i = 0; i < 13; i++) {
        while (n >= values[i]) {
            n -= values[i];
            for (int j = 0; j < strlen(roman[i]); j++) {
                switch (roman[i][j]) {
                    case 'I': roman_counts[0]++; break;
                    case 'V': roman_counts[1]++; break;
                    case 'X': roman_counts[2]++; break;
                    case 'L': roman_counts[3]++; break;
                    case 'C': roman_counts[4]++; break;
                    case 'D': roman_counts[5]++; break;
                    case 'M': roman_counts[6]++; break;
                }
            }
        }
    }

    for (int i = 0; i < 7; i++) {
        count[i] += roman_counts[i];
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int count[7] = {0};

    for (int i = 1; i <= n; i++) {
        roman_count(i, count);
    }

    char roman_chars[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    for (int i = 0; i < 7; i++) {
        if (count[i] > 0) {
            printf("%c %d\n", roman_chars[i], count[i]);
        }
    }

    return 0;
}