#include <stdio.h>
#include <string.h>

int main() {
    char str[256];
    scanf("%s", str);

    int boy_count = 0, girl_count = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (i + 2 < len) {
            if (str[i] == 'b' && str[i+1] == 'o' && str[i+2] == 'y') {
                boy_count++;
                i += 2; // Skip the next two characters as they are part of 'boy'
            }
        }
        if (i + 3 < len) {
            if (str[i] == 'g' && str[i+1] == 'i' && str[i+2] == 'r' && str[i+3] == 'l') {
                girl_count++;
                i += 3; // Skip the next three characters as they are part of 'girl'
            }
        }
    }

    printf("%d\n%d\n", boy_count, girl_count);

    return 0;
}