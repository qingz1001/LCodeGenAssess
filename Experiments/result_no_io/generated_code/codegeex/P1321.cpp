#include <stdio.h>
#include <string.h>

int main() {
    char str[256];
    int l;
    scanf("%s", str);
    l = strlen(str);

    int boy_count = 0;
    int girl_count = 0;

    for (int i = 0; i <= l - 3; i++) {
        if (str[i] == 'b' && str[i + 1] == 'o' && str[i + 2] == 'y') {
            boy_count++;
            i += 2; // Skip the next two characters since they are part of 'boy'
        } else if (str[i] == 'g' && str[i + 1] == 'i' && str[i + 2] == 'r' && str[i + 3] == 'l') {
            girl_count++;
            i += 3; // Skip the next three characters since they are part of 'girl'
        }
    }

    printf("%d\n%d\n", boy_count, girl_count);

    return 0;
}