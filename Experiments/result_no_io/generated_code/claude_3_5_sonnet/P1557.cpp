#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long calculate(char *expr) {
    long long result = 0;
    int sign = 1;
    int i = 0;
    int len = strlen(expr);

    while (i < len) {
        if (expr[i] == '+') {
            sign = 1;
            i++;
        } else if (expr[i] == '-') {
            sign = -1;
            i++;
        } else if (expr[i] == '(') {
            int j = i + 1;
            while (isdigit(expr[j])) j++;
            int multiplier = atoi(expr + i + 1);
            i = j + 1;
            long long num = 0;
            while (i < len && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            result += sign * multiplier * num;
        } else if (isdigit(expr[i])) {
            long long num = 0;
            while (i < len && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            result += sign * num;
        } else {
            i++;
        }
    }

    return result;
}

int main() {
    char expr[2001];
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0;  // Remove newline if present

    long long result = calculate(expr);
    printf("%lld\n", result);

    return 0;
}