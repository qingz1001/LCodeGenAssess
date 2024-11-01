#include <stdio.h>
#include <string.h>

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverseNumber(char *num) {
    int dotIndex = -1;
    for (int i = 0; num[i]; i++) {
        if (num[i] == '.') {
            dotIndex = i;
            break;
        }
    }

    if (dotIndex != -1) {
        reverseString(num);
        reverseString(num + dotIndex + 1);
    } else {
        reverseString(num);
    }
}

int main() {
    char num[50];
    scanf("%s", num);

    reverseNumber(num);

    printf("%s\n", num);

    return 0;
}