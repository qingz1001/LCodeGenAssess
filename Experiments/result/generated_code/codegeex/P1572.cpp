#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void reduceFraction(int *numerator, int *denominator) {
    int g = gcd(*numerator, *denominator);
    *numerator /= g;
    *denominator /= g;
}

int main() {
    char input[101];
    scanf("%s", input);

    int len = strlen(input);
    int numerator = 0, denominator = 1;
    int sign = 1;

    for (int i = 0; i < len; i++) {
        if (input[i] == '/') {
            int temp = 0;
            i++;
            while (i < len && input[i] != '+' && input[i] != '-') {
                temp = temp * 10 + (input[i] - '0');
                i++;
            }
            i--;
            denominator *= temp;
        } else if (input[i] == '+' || input[i] == '-') {
            sign = (input[i] == '+') ? 1 : -1;
        } else {
            int temp = 0;
            while (i < len && input[i] != '/' && input[i] != '+' && input[i] != '-') {
                temp = temp * 10 + (input[i] - '0');
                i++;
            }
            i--;
            numerator = numerator * denominator + sign * temp;
        }
    }

    reduceFraction(&numerator, &denominator);

    if (denominator == 1) {
        printf("%d\n", numerator);
    } else {
        printf("%d/%d\n", numerator, denominator);
    }

    return 0;
}