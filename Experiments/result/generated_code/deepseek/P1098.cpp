#include <stdio.h>
#include <string.h>

void expandString(char *str, int p1, int p2, int p3) {
    int len = strlen(str);
    char result[1000] = {0}; // 假设结果字符串不会超过1000个字符
    int idx = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '-' && i > 0 && i < len - 1) {
            char left = str[i - 1];
            char right = str[i + 1];

            if ((isdigit(left) && isdigit(right)) || (islower(left) && islower(right))) {
                if (left < right) {
                    for (char c = left + 1; c < right; c++) {
                        char fill = c;
                        if (p1 == 2 && islower(c)) {
                            fill = toupper(c);
                        } else if (p1 == 3) {
                            fill = '*';
                        }

                        for (int k = 0; k < p2; k++) {
                            result[idx++] = fill;
                        }
                    }
                    continue;
                } else if (left + 1 == right) {
                    continue; // 直接跳过，因为 left 和 right 是连续的
                }
            }
        }
        result[idx++] = str[i];
    }

    if (p3 == 2) {
        int start = 0, end = idx - 1;
        while (start < end) {
            char temp = result[start];
            result[start] = result[end];
            result[end] = temp;
            start++;
            end--;
        }
    }

    printf("%s\n", result);
}

int main() {
    int p1, p2, p3;
    char str[101];

    scanf("%d %d %d", &p1, &p2, &p3);
    scanf("%s", str);

    expandString(str, p1, p2, p3);

    return 0;
}