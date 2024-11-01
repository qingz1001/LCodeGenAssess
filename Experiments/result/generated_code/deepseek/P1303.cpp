#include <stdio.h>
#include <string.h>

#define MAX_LEN 2001

void multiply(char *num1, char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int res[MAX_LEN * 2] = {0};

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + res[i + j + 1];
            res[i + j + 1] = sum % 10;
            res[i + j] += sum / 10;
        }
    }

    int idx = 0;
    while (idx < len1 + len2 && res[idx] == 0) {
        idx++;
    }

    for (int i = idx; i < len1 + len2; i++) {
        result[i - idx] = res[i] + '0';
    }
    result[len1 + len2 - idx] = '\0';
}

int main() {
    char num1[MAX_LEN], num2[MAX_LEN], result[MAX_LEN * 2];
    scanf("%s", num1);
    scanf("%s", num2);

    multiply(num1, num2, result);

    printf("%s\n", result);

    return 0;
}