#include <stdio.h>
#include <string.h>

int main() {
    char s[256];
    scanf("%s", s);
    int len = strlen(s);
    int boy_count = 0;
    int girl_count = 0;

    for (int i = 0; i <= len - 3; i++) {
        if (s[i] == 'b' && s[i + 1] == 'o' && s[i + 2] == 'y') {
            boy_count++;
            i += 2; // Skip the next two characters to avoid overlapping
        } else if (s[i] == 'g' && s[i + 1] == 'i' && s[i + 2] == 'r' && s[i + 3] == 'l' && s[i + 4] == 'l') {
            girl_count++;
            i += 4; // Skip the next four characters to avoid overlapping
        }
    }

    printf("%d\n%d\n", boy_count, girl_count);

    return 0;
}