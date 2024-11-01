#include <stdio.h>
#include <string.h>

int main() {
    char s[256];
    int a = 0, b = 0, c = 0;
    scanf("%s", s);
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == 'a') {
            if (s[i + 3] == 'a') {
                a = a;
            } else if (s[i + 3] == 'b') {
                a = b;
            } else if (s[i + 3] == 'c') {
                a = c;
            } else {
                a = s[i + 3] - '0';
            }
        } else if (s[i] == 'b') {
            if (s[i + 3] == 'a') {
                b = a;
            } else if (s[i + 3] == 'b') {
                b = b;
            } else if (s[i + 3] == 'c') {
                b = c;
            } else {
                b = s[i + 3] - '0';
            }
        } else if (s[i] == 'c') {
            if (s[i + 3] == 'a') {
                c = a;
            } else if (s[i + 3] == 'b') {
                c = b;
            } else if (s[i + 3] == 'c') {
                c = c;
            } else {
                c = s[i + 3] - '0';
            }
        }
    }
    printf("%d %d %d\n", a, b, c);
    return 0;
}