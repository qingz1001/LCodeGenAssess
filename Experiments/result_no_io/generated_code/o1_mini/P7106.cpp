#include <stdio.h>
#include <stdint.h>

int main(){
    char s[8];
    unsigned int r, g, b;
    scanf("%7s", s);
    sscanf(s+1, "%2x%2x%2x", &r, &g, &b);
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
    printf("#%02X%02X%02X\n", r, g, b);
    return 0;
}