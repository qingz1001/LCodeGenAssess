#include <stdio.h>
#include <ctype.h>

int hex_to_int(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'f') return c - 'a' + 10;
    else if ('A' <= c && c <= 'F') return c - 'A' + 10;
    return 0;
}

void int_to_hex(int num, char *high, char *low) {
    int high_nibble = num / 16;
    int low_nibble = num % 16;
    if (high_nibble < 10) *high = '0' + high_nibble;
    else *high = 'A' + (high_nibble - 10);
    if (low_nibble < 10) *low = '0' + low_nibble;
    else *low = 'A' + (low_nibble - 10);
}

int main(){
    char s[8];
    scanf("%7s", s);
    int r = hex_to_int(s[1]) * 16 + hex_to_int(s[2]);
    int g = hex_to_int(s[3]) * 16 + hex_to_int(s[4]);
    int b = hex_to_int(s[5]) * 16 + hex_to_int(s[6]);
    int r_rev = 255 - r;
    int g_rev = 255 - g;
    int b_rev = 255 - b;
    char rh, rl, gh, gl, bh, bl;
    int_to_hex(r_rev, &rh, &rl);
    int_to_hex(g_rev, &gh, &gl);
    int_to_hex(b_rev, &bh, &bl);
    printf("#%c%c%c%c%c%c\n", rh, rl, gh, gl, bh, bl);
    return 0;
}