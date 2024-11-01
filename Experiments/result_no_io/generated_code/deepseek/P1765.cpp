#include <stdio.h>
#include <string.h>

int main() {
    char sentence[201];
    scanf("%[^\n]", sentence);

    int keyPresses = 0;
    int len = strlen(sentence);

    for (int i = 0; i < len; i++) {
        char c = sentence[i];
        if (c == ' ') {
            keyPresses += 1; // 空格键按一次
        } else if (c >= 'a' && c <= 'o') {
            keyPresses += (c - 'a') % 3 + 1; // 'a' to 'o' 每组3个字母
        } else if (c >= 'p' && c <= 's') {
            keyPresses += c - 'p' + 1; // 'p' to 's' 每组4个字母
        } else if (c >= 't' && c <= 'v') {
            keyPresses += c - 't' + 1; // 't' to 'v' 每组3个字母
        } else if (c >= 'w' && c <= 'z') {
            keyPresses += c - 'w' + 1; // 'w' to 'z' 每组4个字母
        }
    }

    printf("%d\n", keyPresses);
    return 0;
}