#include <stdio.h>
#include <string.h>

int main() {
    char str[101];
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] != 'C' && str[i] != 'A' && str[i] != 'M' && str[i] != 'B' && str[i] != 'R' && str[i] != 'I' && str[i] != 'D' && str[i] != 'G' && str[i] != 'E') {
            printf("%c", str[i]);
        }
    }
    return 0;
}