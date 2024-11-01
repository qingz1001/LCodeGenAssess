#include <stdio.h>
#include <string.h>

int main() {
    char hex[8];
    scanf("%s", hex);

    for (int i = 1; i <= 6; i += 2) {
        int value = (hex[i] >= '0' && hex[i] <= '9') ? (hex[i] - '0') : ((hex[i] - 'A') + 10);
        int reverse_value = 15 - value;
        printf("%c%c", (reverse_value / 16) + '0', (reverse_value % 16) + '0');
    }

    return 0;
}