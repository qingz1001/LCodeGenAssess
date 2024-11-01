#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char word[11], text[1000001];
    int count = 0, first_pos = -1;
    scanf("%s", word);
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            int j = 0;
            while (i + j < strlen(text) && isalpha(text[i + j])) {
                if (tolower(word[j]) != tolower(text[i + j])) break;
                j++;
            }
            if (j == strlen(word)) {
                if (first_pos == -1) first_pos = i;
                count++;
            }
        }
    }
    printf("%d %d\n", count, first_pos);
    return 0;
}