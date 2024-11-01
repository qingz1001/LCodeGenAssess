#include <stdio.h>
#include <string.h>

int getKeyPresses(char c) {
    if (c == ' ') return 1;
    if (c <= 'c') return c - 'a' + 1;
    if (c <= 'f') return c - 'c' + 3;
    if (c <= 'i') return c - 'f' + 3;
    if (c <= 'l') return c - 'i' + 3;
    if (c <= 'o') return c - 'l' + 3;
    if (c <= 's') return c - 'o' + 3;
    if (c <= 'v') return c - 's' + 3;
    return c - 'v' + 3;
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