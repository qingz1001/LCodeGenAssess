#include <stdio.h>
#include <string.h>

#define MAX_LEN 505

void add(char *a, char *b, char *result) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxLen = (lenA > lenB) ? lenA : lenB;
    int carry = 0;

    for (int i = 0; i < maxLen || carry; i++) {
        int digitA = (i < lenA) ? a[lenA - 1 - i] - '0' : 0;
        int digitB = (i < lenB) ? b[lenB - 1 - i] - '0' : 0;
        int sum = digitA + digitB + carry;
        result[maxLen - i] = sum % 10 + '0';
        carry = sum / 10;
    }
    result[maxLen + 1] = '\0';
}

int main() {
    char a[MAX_LEN], b[MAX_LEN];
    char result[MAX_LEN];

    scanf("%s %s", a, b);

    add(a, b, result);

    printf("%s\n", result);

    return 0;
}