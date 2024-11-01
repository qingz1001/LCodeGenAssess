#include <stdio.h>
#include <string.h>

#define MAX_LEN 501

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void add(char *a, char *b, char *result) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_len = len_a > len_b ? len_a : len_b;
    int carry = 0;
    int index = 0;

    reverse(a);
    reverse(b);

    for (int i = 0; i < max_len; i++) {
        int digit_a = (i < len_a) ? a[i] - '0' : 0;
        int digit_b = (i < len_b) ? b[i] - '0' : 0;
        int sum = digit_a + digit_b + carry;
        result[index++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry) {
        result[index++] = carry + '0';
    }

    result[index] = '\0';
    reverse(result);
}

int main() {
    char a[MAX_LEN], b[MAX_LEN], result[MAX_LEN + 1];
    scanf("%s", a);
    scanf("%s", b);

    add(a, b, result);
    printf("%s\n", result);

    return 0;
}