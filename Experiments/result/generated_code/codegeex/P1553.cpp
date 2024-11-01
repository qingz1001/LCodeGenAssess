#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    char input[100];
    scanf("%s", input);

    if (strchr(input, '/')) { // 处理分数
        char *slash = strchr(input, '/');
        *slash = '\0';
        reverse(input);
        char *numerator = input;
        char denominator[100];
        strcpy(denominator, slash + 1);
        reverse(denominator);
        printf("%s/%s\n", numerator, denominator);
    } else if (strchr(input, '.')) { // 处理小数
        char *dot = strchr(input, '.');
        *dot = '\0';
        reverse(input);
        char *integer_part = input;
        char decimal_part[100];
        strcpy(decimal_part, dot + 1);
        reverse(decimal_part);
        while (decimal_part[0] == '0' && decimal_part[1] != '\0') {
            strcpy(decimal_part + 1, decimal_part);
            decimal_part[0] = '0';
        }
        printf("%s.%s\n", integer_part, decimal_part);
    } else if (strchr(input, '%')) { // 处理百分数
        char *percent = strchr(input, '%');
        *percent = '\0';
        reverse(input);
        printf("%s%%\n", input);
    } else { // 处理整数
        reverse(input);
        printf("%s\n", input);
    }

    return 0;
}