#include <stdio.h>
#include <string.h>

int main() {
    char hex[8];
    scanf("%s", hex);

    int r = (hex[1] - '0') * 16 + (hex[2] > '9' ? hex[2] - 'A' + 10 : hex[2] - '0');
    int g = (hex[3] - '0') * 16 + (hex[4] > '9' ? hex[4] - 'A' + 10 : hex[4] - '0');
    int b = (hex[5] - '0') * 16 + (hex[6] > '9' ? hex[6] - 'A' + 10 : hex[6] - '0');

    int reverse_r = 255 - r;
    int reverse_g = 255 - g;
    int reverse_b = 255 - b;

    printf("#");
    if (reverse_r < 10) printf("0");
    printf("%X", reverse_r);
    if (reverse_g < 10) printf("0");
    printf("%X", reverse_g);
    if (reverse_b < 10) printf("0");
    printf("%X\n", reverse_b);

    return 0;
}