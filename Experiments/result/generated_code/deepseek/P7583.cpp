#include <stdio.h>
#include <string.h>

int main() {
    char word[101];
    char forbidden[] = "CAMBRIDGE";
    scanf("%s", word);
    
    for (int i = 0; i < strlen(word); i++) {
        int is_forbidden = 0;
        for (int j = 0; j < strlen(forbidden); j++) {
            if (word[i] == forbidden[j]) {
                is_forbidden = 1;
                break;
            }
        }
        if (!is_forbidden) {
            printf("%c", word[i]);
        }
    }
    printf("\n");
    
    return 0;
}