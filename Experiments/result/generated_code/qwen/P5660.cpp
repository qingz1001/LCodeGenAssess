#include <stdio.h>

int main() {
    char s[9];
    int count = 0;

    scanf("%s", s);

    for (int i = 0; i < 8; i++) {
        if (s[i] == '1') {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}