#include <stdio.h>
#include <string.h>

int main() {
    char word[101];
    char to_remove[] = "CAMBRIDGE";
    int i, j;

    scanf("%s", word);

    for (i = 0; word[i] != '\0'; i++) {
        for (j = 0; to_remove[j] != '\0'; j++) {
            if (word[i] == to_remove[j]) {
                break;
            }
        }
        if (to_remove[j] == '\0') {
            printf("%c", word[i]);
        }
    }

    printf("\n");

    return 0;
}