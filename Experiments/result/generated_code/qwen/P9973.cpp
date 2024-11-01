#include <stdio.h>
#include <string.h>

int main() {
    char s[201];
    scanf("%200s", s);
    
    if (strncmp(s, "You are right, but \"Sao Lei (Winmine)\" is a game whose Chinese name contains two characters while English name contains seven.", 55) == 0) {
        printf("AI\n");
    } else {
        printf("Human\n");
    }
    
    return 0;
}