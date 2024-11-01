#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decimal_to_negative_base(int n, int R) {
    char* result = (char*)malloc(100 * sizeof(char));
    int index = 0;
    int is_negative = (n < 0);
    n = abs(n);

    while (n != 0) {
        int remainder = n % abs(R);
        n /= abs(R);
        if (remainder < 0) {
            remainder += abs(R);
            n += 1;
        }
        if (remainder < 10) {
            result[index++] = remainder + '0';
        } else {
            result[index++] = remainder - 10 + 'A';
        }
    }

    if (index == 0) {
        result[index++] = '0';
    }
    result[index] = '\0';

    // Reverse the result string
    int len = strlen(result);
    for (int i = 0; i < len / 2; i++) {
        char temp = result[i];
        result[i] = result[len - i - 1];
        result[len - i - 1] = temp;
    }

    if (is_negative) {
        for (int i = 0; i < len; i++) {
            result[i] = (result[i] == '0') ? '1' : '0';
        }
    }

    return result;
}

int main() {
    int n, R;
    while (scanf("%d %d", &n, &R) != EOF) {
        char* result = decimal_to_negative_base(n, R);
        printf("%d=%s(base%d)\n", n, result, R);
        free(result);
    }
    return 0;
}