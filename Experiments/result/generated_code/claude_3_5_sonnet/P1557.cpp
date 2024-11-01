#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 2000

int main() {
    char expr[MAX_LEN];
    fgets(expr, MAX_LEN, stdin);

    int result = 0;
    int sign = 1;
    int num = 0;
    int multiplier = 1;

    for (int i = 0; expr[i] != '\0' && expr[i] != '\n'; i++) {
        if (expr[i] == '+') {
            sign = 1;
            multiplier = 1;
        } else if (expr[i] == '-') {
            sign = -1;
            multiplier = 1;
        } else if (expr[i] == '(') {
            int j = i + 1;
            while (isdigit(expr[j])) {
                multiplier = multiplier * 10 + (expr[j] - '0');
                j++;
            }
            i = j;
        } else if (isdigit(expr[i])) {
            num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            result += sign * num * multiplier;
            multiplier = 1;
        }
    }

    printf("%d\n", result);
    return 0;
}