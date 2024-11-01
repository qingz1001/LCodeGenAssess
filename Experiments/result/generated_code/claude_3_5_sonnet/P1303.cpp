#include <stdio.h>
#include <string.h>

#define MAX_LEN 2001

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void multiply(char *num1, char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len_result = len1 + len2;

    for (int i = 0; i < len_result; i++) {
        result[i] = '0';
    }
    result[len_result] = '\0';

    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            int product = (num1[i] - '0') * (num2[j] - '0');
            int sum = product + (result[i + j] - '0');
            result[i + j] = sum % 10 + '0';
            result[i + j + 1] += sum / 10;
        }
    }

    while (len_result > 1 && result[len_result - 1] == '0') {
        len_result--;
    }
    result[len_result] = '\0';

    reverse(result);
}

int main() {
    char num1[MAX_LEN], num2[MAX_LEN], result[MAX_LEN * 2];

    scanf("%s", num1);
    scanf("%s", num2);

    reverse(num1);
    reverse(num2);

    multiply(num1, num2, result);

    printf("%s\n", result);

    return 0;
}