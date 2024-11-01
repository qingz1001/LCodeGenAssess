#include <stdio.h>
#include <string.h>

int main() {
    char str[256];
    scanf("%s", str);

    int boy_count = 0;
    int girl_count = 0;

    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == 'b' && str[i + 1] == 'o' && str[i + 2] == 'y') {
            boy_count++;
            i += 3;
        } else if (str[i] == 'g' && str[i + 1] == 'i' && str[i + 2] == 'r' && str[i + 3] == 'l') {
            girl_count++;
            i += 4;
        }
    }

    printf("%d\n%d\n", boy_count, girl_count);
    return 0;
}