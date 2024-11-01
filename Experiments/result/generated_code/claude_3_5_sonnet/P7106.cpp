#include <stdio.h>
#include <string.h>

int hex_to_dec(char c) {
    if(c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

char dec_to_hex(int n) {
    if(n >= 0 && n <= 9) return n + '0';
    return n - 10 + 'A';
}

int main() {
    char color[8];
    scanf("%s", color);
    
    for(int i = 1; i <= 5; i += 2) {
        int value = hex_to_dec(color[i]) * 16 + hex_to_dec(color[i+1]);
        value = 255 - value;
        color[i] = dec_to_hex(value / 16);
        color[i+1] = dec_to_hex(value % 16);
    }
    
    printf("%s\n", color);
    
    return 0;
}