#include <stdio.h>
#include <string.h>

int getKeyPresses(char c) {
    if (c == ' ') return 1;
    if (c <= 'c') return c - 'a' + 1;
    if (c <= 'f') return c - 'c';
    if (c <= 'i') return c - 'f';
    if (c <= 'l') return c - 'i';
    if (c <= 'o') return c - 'l';
    if (c <= 's') return c - 'o';
    if (c <= 'v') return c - 's';
    return c - 'v';
}

int main() {
    char sentence[201];
    fgets(sentence, sizeof(sentence), stdin);
    
    int total_presses = 0;
    for (int i = 0; sentence[i] != '\0' && sentence[i] != '\n'; i++) {
        total_presses += getKeyPresses(sentence[i]);
    }
    
    printf("%d\n", total_presses);
    return 0;
}