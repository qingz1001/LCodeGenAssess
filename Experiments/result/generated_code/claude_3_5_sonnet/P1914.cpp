#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 51  // 最大字符串长度为50，加1为了存放字符串结束符'\0'

void caesarCipher(char *str, int n) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = ((str[i] - 'a' + n) % 26) + 'a';
    }
}

int main() {
    int n;
    char str[MAX_LENGTH];

    scanf("%d", &n);
    scanf("%s", str);

    caesarCipher(str, n);

    printf("%s\n", str);

    return 0;
}