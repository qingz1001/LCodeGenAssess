#include <stdio.h>
#include <string.h>

int main() {
    char s[51];
    int fingers[8] = {0}; // 指尖分别为：小指、无名指、中指、食指、左大拇指、右大拇指、左环指、右环指
    scanf("%s", s);

    for (int i = 0; i < strlen(s); i++) {
        switch (s[i]) {
            case 'A': case 'S': case 'D': case 'F': case 'J': case 'K': case 'L': case ';':
                fingers[0]++; // 小指
                break;
            case 'W': case 'E': case 'R': case 'T': case 'U': case 'I': case 'O': case 'P':
                fingers[1]++; // 无名指
                break;
            case 'Q': case 'Z': case 'X': case 'C': case 'V': case 'B': case 'N': case 'M':
                fingers[2]++; // 中指
                break;
            case 'Y':
                fingers[3]++; // 食指
                break;
            default:
                if (i > 0 && s[i - 1] == ' ') {
                    fingers[4]++; // 左大拇指
                } else {
                    fingers[5]++; // 右大拇指
                }
                break;
        }
    }

    for (int i = 0; i < 8; i++) {
        printf("%d\n", fingers[i]);
    }

    return 0;
}