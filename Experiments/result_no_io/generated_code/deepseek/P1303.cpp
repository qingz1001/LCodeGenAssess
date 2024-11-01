#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 2001

void multiply(char *num1, char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len = len1 + len2;
    int *temp = (int *)calloc(len, sizeof(int));

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            temp[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
        }
    }

    for (int i = len - 1; i > 0; i--) {
        temp[i - 1] += temp[i] / 10;
        temp[i] %= 10;
    }

    int index = 0;
    while (index < len && temp[index] == 0) {
        index++;
    }

    if (index == len) {
        result[0] = '0';
        result[1] = '\0';
    } else {
        for (int i = index, j = 0; i < len; i++, j++) {
            result[j] = temp[i] + '0';
        }
        result[len - index] = '\0';
    }

    free(temp);
}

int main() {
    char num1[MAX_LEN], num2[MAX_LEN], result[MAX_LEN * 2];
    scanf("%s", num1);
    scanf("%s", num2);

    multiply(num1, num2, result);
    printf("%s\n", result);

    return 0;
}