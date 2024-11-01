#include <stdio.h>
#include <string.h>

int main() {
    char str[256];
    int boy_count = 0, girl_count = 0;

    scanf("%s", str);

    for (int i = 0; i <= strlen(str) - 3; i++) {
        if (str[i] == 'b' && str[i + 1] == 'o' && str[i + 2] == 'y') {
            boy_count++;
            i += 2;
        } else if (str[i] == 'g' && str[i + 1] == 'i' && str[i + 2] == 'r' && str[i + 3] == 'l') {
            girl_count++;
            i += 3;
        }
    }

    printf("%d\n%d\n", boy_count, girl_count);

    return 0;
}