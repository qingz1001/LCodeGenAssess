#include <stdio.h>
#include <string.h>

int main() {
    char word[101];
    scanf("%s", word);
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        if (word[i] != 'C' && word[i] != 'A' && word[i] != 'M' && word[i] != 'B' && word[i] != 'R' && word[i] != 'I' && word[i] != 'D' && word[i] != 'G' && word[i] != 'E') {
            printf("%c", word[i]);
        }
    }
    printf("\n");
    return 0;
}