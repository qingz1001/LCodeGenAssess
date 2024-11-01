#include <stdio.h>
#include <string.h>

char roman[] = "IVXLCDM";
int count[7] = {0};

void toRoman(int n) {
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    for (int i = 0; i < 13; i++) {
        while (n >= values[i]) {
            n -= values[i];
            for (int j = 0; symbols[i][j]; j++) {
                count[strchr(roman, symbols[i][j]) - roman]++;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        toRoman(i);
    }
    
    for (int i = 0; i < 7; i++) {
        if (count[i] > 0) {
            printf("%c %d\n", roman[i], count[i]);
        }
    }
    
    return 0;
}