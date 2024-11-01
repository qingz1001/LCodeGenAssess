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

            if ((left >= 'a' && left <= 'z' && right >= 'a' && right <= 'z' && right > left) ||
                (left >= '0' && left <= '9' && right >= '0' && right <= '9' && right > left)) {
                if (right == left + 1) {
                    // 直接跳过，因为 right 是 left 的后继
                    continue;
                }

                for (char c = left + 1; c < right; c++) {
                    char fill = c;
                    if (p1 == 2 && c >= 'a' && c <= 'z') {
                        fill = c - 'a' + 'A';
                    } else if (p1 == 3) {
                        fill = '*';
                    }

                    for (int j = 0; j < p2; j++) {
                        result[idx++] = fill;
                    }
                }

                if (p3 == 2) {
                    int start = idx - (right - left - 1) * p2;
                    int end = idx - 1;
                    while (start < end) {
                        char temp = result[start];
                        result[start] = result[end];
                        result[end] = temp;
                        start++;
                        end--;
                    }
                }

                continue;
            }
        }
        result[idx++] = str[i];
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