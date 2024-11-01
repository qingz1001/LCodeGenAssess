#include <stdio.h>
#include <string.h>

void invertColor(char *hexColor) {
    int r, g, b;
    sscanf(hexColor + 1, "%2x%2x%2x", &r, &g, &b);
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
    printf("#%02X%02X%02X\n", r, g, b);
}

int main() {
    char hexColor[8];
    scanf("%s", hexColor);
    invertColor(hexColor);
    return 0;
}