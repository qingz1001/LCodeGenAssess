#include <stdio.h>
#include <string.h>

int main() {
    char expression[60001];
    long long result = 0;
    int sign = 1;
    int num = 0;

    scanf("%s", expression);

    for (int i = 0; i <= strlen(expression); i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            num = num * 10 + (expression[i] - '0');
        } else {
            result += sign * num;
            num = 0;
            if (i < strlen(expression)) {
                if (expression[i] == '-') {
                    sign = -1;
                } else {
                    sign = 1;
                }
            }
        }
    }

    printf("%lld\n", result);
    return 0;
}