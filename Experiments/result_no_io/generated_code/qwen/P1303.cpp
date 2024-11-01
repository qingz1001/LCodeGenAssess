#include <stdio.h>
#include <string.h>

#define MAX_LEN 4005

void multiply(char *a, char *b, char *result) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int lenResult = lenA + lenB;
    memset(result, 0, sizeof(char) * (lenResult + 1));

    for (int i = lenA - 1; i >= 0; --i) {
        for (int j = lenB - 1; j >= 0; --j) {
            int digitA = a[i] - '0';
            int digitB = b[j] - '0';
            int product = digitA * digitB;
            int sum = result[i + j + 1] + product;

            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    // Remove leading zeros
    int start = 0;
    while (start < lenResult && result[start] == 0) {
        ++start;
    }

    if (start == lenResult) {
        printf("0\n");
    } else {
        for (; start < lenResult; ++start) {
            printf("%d", result[start]);
        }
        printf("\n");
    }
}

int main() {
    char a[MAX_LEN], b[MAX_LEN];
    char result[MAX_LEN];

    scanf("%s %s", a, b);

    multiply(a, b, result);

    return 0;
}