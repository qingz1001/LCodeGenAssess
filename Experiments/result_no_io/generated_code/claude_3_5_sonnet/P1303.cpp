#include <stdio.h>
#include <string.h>

#define MAX 4010

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void multiply(char *a, char *b, char *result) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int product[MAX] = {0};

    reverse(a);
    reverse(b);

    for (int i = 0; i < len_a; i++) {
        for (int j = 0; j < len_b; j++) {
            product[i + j] += (a[i] - '0') * (b[j] - '0');
        }
    }

    for (int i = 0; i < MAX - 1; i++) {
        product[i + 1] += product[i] / 10;
        product[i] %= 10;
    }

    int idx = MAX - 1;
    while (idx > 0 && product[idx] == 0) {
        idx--;
    }

    int result_idx = 0;
    while (idx >= 0) {
        result[result_idx++] = product[idx] + '0';
        idx--;
    }
    result[result_idx] = '\0';
}

int main() {
    char a[MAX], b[MAX], result[MAX];

    scanf("%s", a);
    scanf("%s", b);

    multiply(a, b, result);

    printf("%s\n", result);

    return 0;
}