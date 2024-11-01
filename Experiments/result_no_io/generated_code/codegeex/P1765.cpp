#include <stdio.h>

int main() {
    char s[200];
    int num = 0;
    scanf("%s", s);

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            num += 1;
        } else if (s[i] == 'a' || s[i] == 'd' || s[i] == 'g' || s[i] == 'j' || s[i] == 'm' || s[i] == 'p' || s[i] == 't' || s[i] == 'w' || s[i] == 'z') {
            num += 1;
        } else if (s[i] == 'b' || s[i] == 'e' || s[i] == 'h' || s[i] == 'k' || s[i] == 'n' || s[i] == 'q' || s[i] == 'u' || s[i] == 'x') {
            num += 2;
        } else if (s[i] == 'c' || s[i] == 'f' || s[i] == 'i' || s[i] == 'l' || s[i] == 'o' || s[i] == 'r' || s[i] == 'v' || s[i] == 'y') {
            num += 3;
        } else if (s[i] == 's' || s[i] == 'x') {
            num += 4;
        }
    }

    printf("%d\n", num);
    return 0;
}