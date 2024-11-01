#include <stdio.h>
#include <string.h>

int main() {
    char s[51];
    scanf("%s", s);
    int n = strlen(s);
    int fingers[8] = {0}; // 初始化每根手指的按键次数

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c >= 'A' && c <= 'L') {
            if (c >= 'A' && c <= 'C') {
                fingers[0]++; // 小指
            } else if (c >= 'D' && c <= 'F') {
                fingers[1]++; // 无名指
            } else if (c >= 'G' && c <= 'I') {
                fingers[2]++; // 中指
            } else if (c >= 'J' && c <= 'L') {
                fingers[3]++; // 食指
            }
        } else if (c >= 'M' && c <= 'R') {
            if (c >= 'M' && c <= 'O') {
                fingers[4]++; // 食指
            } else if (c >= 'P' && c <= 'Q') {
                fingers[5]++; // 中指
            } else if (c >= 'R') {
                fingers[6]++; // 无名指
            }
        } else if (c >= 'S' && c <= 'Z') {
            if (c >= 'S' && c <= 'V') {
                fingers[7]++; // 小指
            } else if (c >= 'W' && c <= 'Z') {
                fingers[6]++; // 无名指
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        printf("%d\n", fingers[i]);
    }

    return 0;
}