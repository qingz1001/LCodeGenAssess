#include <stdio.h>
#include <string.h>

int main() {
    char sentence[201];
    scanf("%[^\n]", sentence);

    int keyPressCount = 0;
    int len = strlen(sentence);

    for (int i = 0; i < len; i++) {
        char c = sentence[i];
        if (c == ' ') {
            keyPressCount += 1; // 空格键按一次
        } else if (c >= 'a' && c <= 'c') {
            keyPressCount += (c - 'a') % 3 + 1; // 2键
        } else if (c >= 'd' && c <= 'f') {
            keyPressCount += (c - 'd') % 3 + 1; // 3键
        } else if (c >= 'g' && c <= 'i') {
            keyPressCount += (c - 'g') % 3 + 1; // 4键
        } else if (c >= 'j' && c <= 'l') {
            keyPressCount += (c - 'j') % 3 + 1; // 5键
        } else if (c >= 'm' && c <= 'o') {
            keyPressCount += (c - 'm') % 3 + 1; // 6键
        } else if (c >= 'p' && c <= 's') {
            keyPressCount += (c - 'p') % 4 + 1; // 7键
        } else if (c >= 't' && c <= 'v') {
            keyPressCount += (c - 't') % 3 + 1; // 8键
        } else if (c >= 'w' && c <= 'z') {
            keyPressCount += (c - 'w') % 4 + 1; // 9键
        }
    }

    printf("%d\n", keyPressCount);
    return 0;
}