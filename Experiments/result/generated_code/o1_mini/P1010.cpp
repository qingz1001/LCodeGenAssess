#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 100000

char buffer[MAX_BUFFER];
int pos = 0;

void append_char(char c) {
    if (pos < MAX_BUFFER - 1) {
        buffer[pos++] = c;
    }
}

void append_str(const char* s) {
    while (*s) {
        append_char(*s++);
    }
}

void represent(int n);

void represent(int n) {
    if (n == 0) {
        append_str("0");
        return;
    }
    int bits[32];
    int count = 0;
    for(int i = 0; i < 32; i++) {
        if (n & (1 << i)) {
            bits[count++] = i;
        }
    }
    for(int i = count - 1; i >=0; i--) {
        append_str("2(");
        represent(bits[i]);
        append_char(')');
        if(i != 0){
            append_char('+');
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    represent(n);
    buffer[pos] = '\0';
    printf("%s", buffer);
    return 0;
}