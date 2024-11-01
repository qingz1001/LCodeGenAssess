#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 51  // 50个字符加上'\0'

void caesarCipher(char *str, int n) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
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