#include <stdio.h>
#include <string.h>

void reverseInteger(char *num) {
    int len = strlen(num);
    for (int i = 0; i < len / 2; i++) {
        char temp = num[i];
        num[i] = num[len - i - 1];
        num[len - i - 1] = temp;
    }
}

void reverseDecimal(char *num, int dotIndex) {
    reverseInteger(num + dotIndex + 1);
}

void reverseFraction(char *num, int slashIndex) {
    reverseInteger(num + slashIndex + 1);
    reverseInteger(num);
}

void reversePercentage(char *num, int percentIndex) {
    reverseInteger(num + percentIndex + 1);
}

int main() {
    char s[50];
    scanf("%s", s);

    int len = strlen(s);
    int dotIndex = -1;
    int slashIndex = -1;
    int percentIndex = -1;

    for (int i = 0; i < len; i++) {
        if (s[i] == '.') {
            dotIndex = i;
        } else if (s[i] == '/') {
            slashIndex = i;
        } else if (s[i] == '%') {
            percentIndex = i;
        }
    }

    if (dotIndex != -1) {
        reverseDecimal(s, dotIndex);
    } else if (slashIndex != -1) {
        reverseFraction(s, slashIndex);
    } else if (percentIndex != -1) {
        reversePercentage(s, percentIndex);
    } else {
        reverseInteger(s);
    }

    printf("%s\n", s);

    return 0;
}