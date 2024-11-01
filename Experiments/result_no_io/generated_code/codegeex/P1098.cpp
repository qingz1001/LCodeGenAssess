#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    int p1, p2, p3;
    scanf("%d%d%d", &p1, &p2, &p3);
    char str[101];
    scanf("%s", str);
    int len = strlen(str);
    char result[101 * 8];
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '-') {
            char start = str[i - 1];
            char end = str[i + 1];
            if ((isdigit(start) && isdigit(end) && end > start) ||
                (islower(start) && islower(end) && end > start)) {
                for (char c = start + 1; c < end; c++) {
                    for (int k = 0; k < p2; k++) {
                        if (p1 == 1) {
                            result[index++] = (islower(start) ? c : c - 'a' + 'A');
                        } else if (p1 == 2) {
                            result[index++] = (islower(start) ? c - 'a' + 'A' : c);
                        } else {
                            result[index++] = '*';
                        }
                    }
                }
            } else {
                result[index++] = '-';
            }
        } else {
            result[index++] = str[i];
        }
    }

    if (p3 == 2) {
        for (int i = 0; i < index / 2; i++) {
            char temp = result[i];
            result[i] = result[index - i - 1];
            result[index - i - 1] = temp;
        }
    }

    result[index] = '\0';
    printf("%s\n", result);
    return 0;
}