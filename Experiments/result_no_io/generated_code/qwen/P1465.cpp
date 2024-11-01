#include <stdio.h>
#include <string.h>

void countRomanDigits(int n) {
    char roman[] = "IVXLCDM";
    int values[] = {4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    int counts[13] = {0};

    for (int i = 12; i >= 0; i--) {
        while (n >= values[i]) {
            n -= values[i];
            counts[i]++;
        }
    }

    for (int i = 0; i < 13; i++) {
        if (counts[i] > 0) {
            printf("%c %d\n", roman[i], counts[i]);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    countRomanDigits(n);
    return 0;
}