#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long calculate(char *expression) {
    long long result = 0;
    long long current_num = 0;
    int sign = 1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (isdigit(expression[i])) {
            current_num = current_num * 10 + (expression[i] - '0');
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i + 1] == '\0') {
            result += sign * current_num;
            current_num = 0;
            sign = (expression[i] == '+') ? 1 : -1;
        }
    }

    return result;
}

int main() {
    char expression[60001];
    fgets(expression, sizeof(expression), stdin);

    // 移除可能存在的换行符
    expression[strcspn(expression, "\n")] = 0;

    long long result = calculate(expression);
    printf("%lld\n", result);

    return 0;
}