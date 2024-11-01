#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2005

int calculate(char *expression) {
    int result = 0;
    char *token = strtok(expression, "+-");
    while (token != NULL) {
        if (*token == '(') {
            token++;
            int sign = 1;
            if (*token == '-') {
                sign = -1;
                token++;
            }
            int count = 0;
            while (*token >= '0' && *token <= '9') {
                count = count * 10 + (*token - '0');
                token++;
            }
            result += sign * count;
        } else {
            int number = atoi(token);
            result += number;
        }
        token = strtok(NULL, "+-");
    }
    return result;
}

int main() {
    char expression[MAX_LEN];
    scanf("%s", expression);
    printf("%d\n", calculate(expression));
    return 0;
}